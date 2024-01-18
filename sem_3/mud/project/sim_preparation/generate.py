from enum import Enum
from pathlib import Path
import pathlib
from typing import Dict

import jinja2
import yaml
from pydantic import BaseModel, ValidationError
from .data_preprocessing import solve_initial_conditions


class Simulation(str, Enum):
    TIME_DOMAIN = "time_domain"


SIMULATION_SIMULINK_MODEL_PATH_MAP: Dict[Simulation, Path] = {
    Simulation.TIME_DOMAIN: pathlib.Path("./simulink_models/time_domain.slx")
    .absolute()
    .__str__(),
}

SIMULATION_TEMPLATE_MAP: Dict[Simulation, str] = {
    Simulation.TIME_DOMAIN: "time_domain.m.j2",
}


class TimeDomainSimConfig(BaseModel):
    ROOM_HEAT_CAPACITY: str
    AIR_HEAT: str

    SIMULATION_TIME_SECONDS: str
    SIMULATION_STEP_SIZE: str
    PLOT_TITLE: str

    STEP_TIME_SECONDS: str
    OUTSIDE_TEMP_STEP_SIZE_CELSIUS: str
    INFLOW_TEMP_STEP_SIZE_CELSIUS: str
    INFLOW_POWER_STEP_SIZE: str
    OUTSIDE_TEMP_NOMINAL_CELSIUS: str
    ROOM_1_TEMP_NOMINAL_CELSIUS: str
    ROOM_2_TEMP_NOMINAL_CELSIUS: str
    INFLOW_TEMP_NOMINAL_CELSIUS: str
    INFLOW_POWER_NOMINAL: str
    OUTSIDE_WALL_TEMP_LOSS_COEFF_NOMINAL: str
    ROOM_1_WALL_TEMP_LOSS_COEFF_NOMINAL: str
    ROOM_2_WALL_TEMP_LOSS_COEFF_NOMINAL: str
    OUTSIDE_TEMP_INITIAL_CELSIUS_VEC: list[float]
    INFLOW_TEMP_INITIAL_CELSIUS_VEC: list[float]
    INFLOW_POWER_INITIAL_VEC: list[float]


class TimeDomainSimData(TimeDomainSimConfig):
    SIMULATION_PATH: str
    ROOM_TEMP_1_INITIAL_CELSIUS: list[float]
    ROOM_TEMP_2_INITIAL_CELSIUS: list[float]

    @staticmethod
    def from_config(config: TimeDomainSimConfig, simulation: Simulation):
        room_1_initial_temps = []
        room_2_initial_temps = []
        for outside_temp, inflow_temp, inflow_power in zip(
            config.OUTSIDE_TEMP_INITIAL_CELSIUS_VEC,
            config.INFLOW_TEMP_INITIAL_CELSIUS_VEC,
            config.INFLOW_POWER_INITIAL_VEC,
        ):
            (
                temp_room_1_initial_celsius,
                temp_room_2_initial_celsius,
            ) = solve_initial_conditions(
                float(config.ROOM_HEAT_CAPACITY) * float(config.AIR_HEAT),
                float(inflow_power),
                float(outside_temp),
                float(inflow_temp),
                float(config.OUTSIDE_WALL_TEMP_LOSS_COEFF_NOMINAL),
                float(config.ROOM_1_WALL_TEMP_LOSS_COEFF_NOMINAL),
                float(config.ROOM_2_WALL_TEMP_LOSS_COEFF_NOMINAL),
            )
            room_1_initial_temps.append(temp_room_1_initial_celsius)
            room_2_initial_temps.append(temp_room_2_initial_celsius)

        return TimeDomainSimData(
            SIMULATION_PATH=SIMULATION_SIMULINK_MODEL_PATH_MAP[simulation],
            ROOM_TEMP_1_INITIAL_CELSIUS=room_1_initial_temps,
            ROOM_TEMP_2_INITIAL_CELSIUS=room_2_initial_temps,
            **config.dict(),
        )


def get_configs_from_yaml(
    simulation: Simulation, file_path: str
) -> Dict[str, Dict[str, str]]:
    with open(file_path, "r") as file:
        data = yaml.safe_load(file)

    subsections = {}
    for key, value in data.items():
        if isinstance(value, dict):
            subsections[key] = value
        subsections[key]["SIMULATION_PATH"] = SIMULATION_SIMULINK_MODEL_PATH_MAP[
            simulation
        ]

    return subsections


def get_sim_data(simulation: Simulation, config_path: str) -> Dict[str, Dict[str, str]]:
    configs = get_configs_from_yaml(simulation, config_path)
    config_data: Dict[str, Dict[str, str]] = {}
    match simulation:
        case Simulation.TIME_DOMAIN:
            for sim_name, config in configs.items():
                config_data[sim_name] = TimeDomainSimData.from_config(
                    TimeDomainSimConfig(**config), simulation=simulation
                ).dict()
    return config_data


def validate_configs(simlulation: Simulation, configs: Dict[str, Dict[str, str]]):
    def _validate(config: Dict[str, str]):
        match simlulation:
            case Simulation.TIME_DOMAIN:
                TimeDomainSimConfig(**config)
            case _:
                raise ValueError(f"Invalid simulation: {simlulation}")

    for key, value in configs.items():
        try:
            _validate(value)
        except ValidationError as e:
            raise ValueError(f"Invalid config: {key}") from e


def generate_script(
    template_name: str, output_path: str, template_config: Dict[str, str]
):
    template_loader = jinja2.FileSystemLoader(searchpath="./templates")
    template_env = jinja2.Environment(loader=template_loader)
    template = template_env.get_template(template_name)
    output_text = template.render(**template_config)
    with open(output_path, "w") as file:
        file.write(output_text)


def generate_matlab(simulation: Simulation, config_path: str, output_dir: str):
    configs = get_sim_data(simulation, config_path)
    print(configs)
    # validate_configs(simulation, configs)

    for sim_name, config in configs.items():
        template_name = SIMULATION_TEMPLATE_MAP[simulation]
        output_path = f"{output_dir}/{sim_name}.m"
        generate_script(template_name, output_path, config)
