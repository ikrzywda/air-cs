from math import sqrt
from typing import List, Tuple

from pydantic import BaseModel


class Uncertainty(BaseModel):
    uncertainty: float
    lsd_magnitude: float
    c_constant: int


class DeviceUncertainty(BaseModel):
    device_name: str
    probing_specs: List[Tuple[float, Uncertainty]]


def compute_uncertainty(input_value: float, device_specs: DeviceUncertainty) -> float:
    uncertainty = next(
        (
            uncertainty_spec
            for range, uncertainty_spec in device_specs.probing_specs
            if input_value < range
        ),
        None,
    )

    uncertainty = device_specs.probing_specs[0][1]

    return abs(
        input_value * uncertainty.uncertainty
        + (uncertainty.c_constant * uncertainty.lsd_magnitude)
    ) / sqrt(3)
