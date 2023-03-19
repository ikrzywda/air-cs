from cmath import sqrt
import sys

import matplotlib
import numpy as np

sys.path.insert(0, "../")

from typing import List, Optional

import pandas as pd
from matplotlib import pyplot as plt
import statsmodels.api  as sm
from processing.devices import BRYMEN_BM811_CURRENT, BRYMEN_BM811_VOLTAGE
from processing.latex import dataframe_to_latex_table
from processing.linear_regression import LinearRegressionData, get_regression
from processing.sanitization import get_sample_data
from processing.uncertainty import compute_uncertainty
from sigfig import round


ZENER_DIODE_DATA_FILES = [
    (
        "zener_2",
        "data/multimeter_data/sanitized/zener-p-2.csv",
        "data/multimeter_data/sanitized/zener-z-2.csv",
    ),
    (
        "zener_3",
        "data/multimeter_data/sanitized/zener-p-3.csv",
        "data/multimeter_data/sanitized/zener-z-3.csv",
    ),
    (
        "zener_4",
        "data/multimeter_data/sanitized/zener-p-4.csv",
        "data/multimeter_data/sanitized/zener-z-4.csv",
    ),
]


def prepare_data(path: str, sort_ascending: Optional[bool] = True) -> pd.DataFrame:
    df = pd.read_csv(path, index_col=False, header=0)
    df.sort_values(by="U", ascending=sort_ascending)

    df["u(U)"] = [compute_uncertainty(v, BRYMEN_BM811_VOLTAGE) for v in df["U"]]
    df["u(I)"] = [compute_uncertainty(i, BRYMEN_BM811_CURRENT) for i in df["I"]]

    return df


def merge_data(path_1: str, path_2: str) -> pd.DataFrame:
    df1 = prepare_data(path_1)
    df2 = prepare_data(path_2)
    df_result = pd.concat([df1, df2])

    df_result.sort_values(by="U", inplace=True)
    df_result.drop(df_result.tail(10).index, inplace=True)
    df_result.drop(df_result.head(10).index, inplace=True)

    df_result.to_csv("out.csv")

    return df_result


def plot_zener_with_regression(
    df: pd.DataFrame, forward_sample: int, reverse_sample: int, zener_voltage_index: int, zener_threshold_voltage_index: int
) -> List[LinearRegressionData]:
    forward_regr_voltage = df["U"][-reverse_sample:].to_numpy()
    forward_regr_current = df["I"][-reverse_sample:].to_numpy()

    reverse_regr_voltage = df["U"][:forward_sample].to_numpy()
    reverse_regr_current = df["I"][:forward_sample].to_numpy()

    forward_data, forward_vals, forward_model = get_regression(
        forward_regr_voltage, forward_regr_current
    )
    reverse_data, reverse_vals, reverse_model = get_regression(
        reverse_regr_voltage, reverse_regr_current
    )

    plt.figure()
    plt.grid()
    plt.xlabel("U[mV]")
    plt.ylabel("I[mA]")
    plt.errorbar(
        df["U"], df["I"], xerr=df["u(U)"], yerr=df["u(I)"], zorder=-1, ls="None"
    )
    plt.scatter(df["U"], df["I"], zorder=-1, ls="None", s=2)
    plt.scatter(df["U"][zener_threshold_voltage_index], df["I"][zener_threshold_voltage_index], zorder=1, ls="None", s=10, color="magenta", label="U_zk")
    plt.scatter(df["U"][zener_voltage_index], df["I"][zener_voltage_index], zorder=1, ls="None", s=10, color="black", label="U_z")
    plt.scatter()
    plt.plot(forward_vals, forward_model.predict(forward_vals), color="red")
    plt.plot(reverse_vals, reverse_model.predict(reverse_vals), color="orange")
    plt.legend(loc="upper left")

    return [forward_data, reverse_data]


def plot_with_regression(df: pd.DataFrame) -> LinearRegressionData:
    regr_voltage = df["U"][-30:].to_numpy()
    regr_current = df["I"][-30:].to_numpy()

    data, vals, model = get_regression(regr_voltage, regr_current)

    plt.figure()
    plt.grid()
    plt.xlabel("U[V]")
    plt.ylabel("I[A]")

    plt.errorbar(
        df["U"], df["I"], xerr=df["u(U)"], yerr=df["u(I)"], zorder=-1, ls="None"
    )
    plt.scatter(df["U"], df["I"], zorder=-1, ls="None", s=2)

    plt.plot(vals, model.predict(vals), color="orange")
    plt.plot(vals, model.predict(vals), color="orange")

    plt.show()

    return data


def sample_data_presentation(df_1: pd.DataFrame, df_2: pd.DataFrame) -> pd.DataFrame:
    return pd.concat([df_1[0:40], df_2[0:40]], axis=1)


def get_zener_characteristics(voltage_samples: np.ndarray, current_samples: np.ndarray, min_voltage: float, min_current: float, zener_voltage: float, zener_current: float):

    x = sm.add_constant(voltage_samples)
    model = sm.OLS(current_samples, x)
    results = model.fit()

    a = results.params[1]
    b = results.params[0]
    ua = results.bse[1]
    ub = results.bse[0]

    print("a: ", results.params[1], results.bse[1])
    print("b: ", results.params[0], results.bse[0])
    print("breakthrough voltage: ", -b / a)
    print("breakthrough voltage uncertainty", sqrt(
        (b/(a**2) * ua)**2 + (1/a * ub)**2
    ))
    print("dynamic resistance: ", 1/a, ua / a**2)

    static_resistance = zener_voltage / zener_current
    

    u_zener_voltage = compute_uncertainty(zener_voltage, BRYMEN_BM811_VOLTAGE)
    u_zener_current = compute_uncertainty(zener_current, BRYMEN_BM811_CURRENT)
    u_static_resistance = sqrt(
        ((u_zener_voltage / zener_current)**2 + (zener_voltage * u_zener_current) / (zener_current**2))**2
    )

    print("min voltage: ", min_voltage, compute_uncertainty(min_voltage, BRYMEN_BM811_VOLTAGE))
    print("min current: ", min_current, compute_uncertainty(min_current, BRYMEN_BM811_CURRENT))
    print("zener voltage: ", zener_voltage, compute_uncertainty(zener_voltage, BRYMEN_BM811_VOLTAGE))
    print("zener current: ",zener_current, compute_uncertainty(zener_current, BRYMEN_BM811_CURRENT))
    print("static resistance: ", static_resistance, u_static_resistance)


if __name__ == "__main__":
    matplotlib.use("Agg")
    for name, forward_polarity, reverse_polarity in ZENER_DIODE_DATA_FILES:
        forward = prepare_data(forward_polarity)
        reverse = prepare_data(reverse_polarity)

        sample = sample_data_presentation(forward, reverse)

        data = merge_data(forward_polarity, reverse_polarity)

        sample_forward = get_sample_data(forward, -20)[0:10]
        sample_reverse = get_sample_data(reverse, -20)[-10:]

        sample_forward["I"] = sample_forward["I"].apply(lambda x: round(x, sigfigs=3))
        sample_forward["u(I)"] = sample_forward["u(I)"].apply(lambda x: round(x, sigfigs=2))
        sample_forward["u(U)"] = sample_forward["u(U)"].apply(lambda x: round(x, sigfigs=3))


        sample_reverse["I"] = sample_reverse["I"].apply(lambda x: round(x, sigfigs=4))
        sample_reverse["u(I)"] = sample_reverse["u(I)"].apply(lambda x: round(x, sigfigs=2))
        sample_reverse["u(U)"] = sample_reverse["u(U)"].apply(lambda x: round(x, sigfigs=3))



        # linear_regression_coeffs = plot_zener_with_regression(data, 100, 100)
        # sample_forward = sample_forward.applymap(lambda x: round(x, sigfigs=2))

        print(sample_forward)
        print(sample_reverse)
        sample_forward.reset_index(inplace=True, drop=True)
        sample_reverse.reset_index(inplace=True, drop=True)

        rounded = pd.concat([sample_forward, sample_reverse], axis=1)



        print(rounded)

        # plt.savefig(f"result_assets/figures/{name}.png")
        with open(f"result_assets/latex_tables/{name}.tex", "w") as f:
            f.write(dataframe_to_latex_table(rounded))
