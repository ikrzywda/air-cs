import math

import pandas as pd


def compute_uncertainty(
    value: float, *, uncertainty: float, dgt_uncertainty, dgt_count: int
) -> float:
    return (value * uncertainty + dgt_uncertainty * dgt_count) / math.sqrt(3)


def compute_voltage_uncertainty(
    value: float, *, dgt_uncertainty: float, unit_coeff: float
):
    nominal_value = value * unit_coeff
    uncertainty = 0.005 if nominal_value < 0.4 else 0.009
    return (
        compute_uncertainty(
            value,
            uncertainty=uncertainty,
            dgt_uncertainty=dgt_uncertainty,
            dgt_count=2,
        )
        * unit_coeff
    )


def compute_current_uncertainty(
    value: float, *, dgt_uncertainty: float, unit_coeff: float
):
    nominal_value = value * unit_coeff
    uncertainty = 0.008 if nominal_value < 20 else 0.012
    return (
        compute_uncertainty(
            value,
            uncertainty=uncertainty,
            dgt_uncertainty=dgt_uncertainty,
            dgt_count=1,
        )
        * unit_coeff
    )


def apply_voltage_and_current_uncertainties(df: pd.DataFrame) -> pd.DataFrame:
    df["voltage_uncertainty"] = df.apply(
        lambda row: compute_voltage_uncertainty(
            row["voltage"],
            dgt_uncertainty=row["voltage_dgt"],
            unit_coeff=row["voltage_unit_coeff"],
        ),
        axis=1,
    )
    df["current_uncertainty"] = df.apply(
        lambda row: compute_current_uncertainty(
            row["current"],
            dgt_uncertainty=row["current_dgt"],
            unit_coeff=row["current_unit_coeff"],
        ),
        axis=1,
    )
    df["voltage"] = df.apply(
        lambda row: row["voltage"] * row["voltage_unit_coeff"], axis=1
    )
    df["current"] = df.apply(
        lambda row: row["current"] * row["current_unit_coeff"], axis=1
    )

    df.drop(
        columns=[
            "voltage_unit_coeff",
            "current_unit_coeff",
            "voltage_dgt",
            "current_dgt",
        ],
        inplace=True,
    )

    return df.reindex(
        columns=["voltage", "voltage_uncertainty", "current", "current_uncertainty"]
    )


def apply_wavelength_uncertainties(df: pd.DataFrame) -> pd.DataFrame:
    df["wavelength_uncertainty"] = df.apply(
        lambda row: row["error"] / math.sqrt(3), axis=1
    )
    return df
