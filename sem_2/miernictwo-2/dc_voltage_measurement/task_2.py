from typing import Dict

import pandas as pd

HEADER_U_V = "$U_V [V]$"
HEADER_DELTA_U_V = "$\Delta U_V [V]$"
HEADER_SMALL_DELTA_U_V = "$\delta U_V [%]$"
HEADER_ALPHA = "$\\alpha [dz]$"
HEADER_ALPHA_MAX = "$\\alpha_{max} [dz]$"
HEADER_R_V = "$R_V [\Omega]$"
HEADER_R_W = "$R_W [\Omega]$"
HEADER_DELTA_M_U = "$\Delta m_U [V]$"
HEADER_SMALL_DELTA_M_U = "$\delta m_U [V]$"
HEADER_RANGE_VOLTAGE = "$U_{V zakr} [V]$"


class AnalogMultimeter:
    def __init__(
        self,
        range_volts: float,
        max_slice: int,
        meter_class: float,
        input_resistance: int,
    ):
        self.range_volts = range_volts
        self.max_slice = max_slice
        self.meter_class = meter_class
        self.input_resistance = input_resistance

        self.header_order = [
            HEADER_ALPHA,
            HEADER_ALPHA_MAX,
            HEADER_RANGE_VOLTAGE,
            HEADER_U_V,
            HEADER_R_V,
            HEADER_R_W,
            HEADER_DELTA_M_U,
            HEADER_SMALL_DELTA_M_U,
            HEADER_DELTA_U_V,
            HEADER_SMALL_DELTA_U_V,
        ]

    def compute_voltage_reading(self, reading: int) -> float:
        return reading * (self.range_volts / self.max_slice)

    def compute_base_error(self, reading: int) -> float:
        return (self.meter_class * reading * self.meter_class) / 100

    def create_dataframe(self, readings: Dict[int, float]) -> pd.DataFrame:
        df = pd.DataFrame(list(readings.items()), columns=[HEADER_R_W, HEADER_ALPHA])
        df[HEADER_U_V] = df.apply(
            lambda row: self.compute_voltage_reading(row[HEADER_ALPHA]), axis=1
        )
        df[HEADER_DELTA_U_V] = df.apply(
            lambda row: self.compute_base_error(row[HEADER_ALPHA]), axis=1
        )
        df[HEADER_SMALL_DELTA_U_V] = df.apply(
            lambda row: row[HEADER_DELTA_U_V] / row[HEADER_U_V], axis=1
        )
        df[HEADER_ALPHA_MAX] = df.apply(lambda row: self.max_slice, axis=1)
        df[HEADER_RANGE_VOLTAGE] = df.apply(lambda row: self.range_volts, axis=1)
        df[HEADER_R_V] = df.apply(lambda row: self.input_resistance, axis=1)
        df[HEADER_DELTA_M_U] = df.apply(
            lambda row: row[HEADER_U_V] * row[HEADER_R_W] / self.input_resistance,
            axis=1,
        )
        df[HEADER_SMALL_DELTA_M_U] = df.apply(
            lambda row: -(row[HEADER_R_W] / (self.input_resistance + row[HEADER_R_W])),
            axis=1,
        )

        df = df.reindex(columns=self.header_order)
        return df


class DigitalMultimeter:
    def __init__(
        self,
        u_v: float,
        resolution: float,
        significant_digit_count: int,
        input_resistance: int,
    ):
        self.u_v = u_v
        self.resolution = resolution
        self.significant_digit_count = significant_digit_count
        self.input_resistance = input_resistance

        self.header_order = [
            HEADER_U_V,
            HEADER_DELTA_U_V,
            HEADER_SMALL_DELTA_U_V,
            HEADER_R_V,
            HEADER_R_W,
            HEADER_DELTA_M_U,
            HEADER_SMALL_DELTA_M_U,
        ]

    def compute_base_error(self, a: float) -> float:
        return self.u_v * a / 100

    def compute_measurement_error(self, a: float) -> float:
        base_error = self.compute_base_error(a)
        return base_error + self.resolution * self.significant_digit_count

    def compute_relative_measurement_error(self, a: float) -> float:
        return self.compute_measurement_error(a) / self.u_v

    def create_dataframe(self, measurements: Dict[int, float]) -> pd.DataFrame:
        df = pd.DataFrame(list(measurements.items()), columns=[HEADER_R_W, HEADER_U_V])
        df[HEADER_DELTA_U_V] = df.apply(
            lambda row: self.compute_measurement_error(row[HEADER_U_V]), axis=1
        )
        df[HEADER_SMALL_DELTA_U_V] = df.apply(
            lambda row: self.compute_relative_measurement_error(row[HEADER_U_V]), axis=1
        )
        df[HEADER_R_V] = df.apply(lambda row: self.input_resistance, axis=1)
        df[HEADER_DELTA_M_U] = df.apply(
            lambda row: row[HEADER_U_V] * row[HEADER_R_W] / self.input_resistance,
            axis=1,
        )
        df[HEADER_SMALL_DELTA_M_U] = df.apply(
            lambda row: -(row[HEADER_R_W] / (self.input_resistance + row[HEADER_R_W])),
            axis=1,
        )
        df = df.reindex(columns=self.header_order)
        return df


UNIT_MEASUREMENTS: Dict[int, float] = {
    0: 5.037,
    10: 5.037,
    100: 5.037,
    1_000: 5.036,
    10_000: 5.032,
    100_000: 4.992,
}
UNIT_INTERNAL_RESISTANCE = 10_000_000
UNIT_RESOLUTION = 0.001
UNIT_UNCERTAINTY = 0.3
UNIT_SIGNIFICANT_DIGIT_COUNT = 4

HP_MEASUREMENTS: Dict[int, float] = {
    0: 5.0329,
    10: 5.0327,
    1_000: 5.0321,
    10_000: 5.0277,
    100_000: 4.9827,
}
HP_INTERNAL_RESISTANCE = 10_000_000
HP_RESOLUTION = 0.0001
HP_UNCERTAINTY = 0.05
HP_SIGNIFICANT_DIGIT_COUNT = 4

unit_multimeter = DigitalMultimeter(
    UNIT_UNCERTAINTY,
    UNIT_RESOLUTION,
    UNIT_SIGNIFICANT_DIGIT_COUNT,
    UNIT_INTERNAL_RESISTANCE,
)
output = unit_multimeter.create_dataframe(UNIT_MEASUREMENTS)
print(output)
output.to_csv("unit.csv")

hp_multimeter = DigitalMultimeter(
    HP_UNCERTAINTY,
    HP_RESOLUTION,
    HP_SIGNIFICANT_DIGIT_COUNT,
    HP_INTERNAL_RESISTANCE,
)
output = hp_multimeter.create_dataframe(HP_MEASUREMENTS)
print(output)
output.to_csv("hp.csv")


LM_3_1_MEASUREMENTS: Dict[int, float] = {
    0: 50,
    10: 50,
    100: 50,
    1_000: 44,
    10_000: 22,
    100_000: 4,
}

lm_3_1_multimeter = AnalogMultimeter(7.5, 75, 0.5, 7_500)

output = lm_3_1_multimeter.create_dataframe(LM_3_1_MEASUREMENTS)
output.to_csv("lm_3_1.csv")
print(output)
