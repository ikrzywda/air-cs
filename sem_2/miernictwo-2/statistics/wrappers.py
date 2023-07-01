import pandas as pd
import numpy as np
from scipy.stats import t

# shouldn't really be hardcoded, but it's fine for now
DEGREES_OF_FREEDOM = 11
TRUST_LEVEL = 0.97
T_STUDENT_CRITICAL_VALUE = t.ppf(1 - TRUST_LEVEL / 2, DEGREES_OF_FREEDOM)

LATEX_ARITHMETIC_MEANS_HEADERS = [
    r"$$\bar{a} \space [mm]$$",
    r"$$\bar{b} \space [mm]$$",
    r"$$\bar{c} \space [mm]$$",
    r"$$\bar{h}_a \space [mm]$$",
    r"$$\bar{h}_b \space [mm]$$",
    r"$$\bar{h}_c \space [mm]$$",
]

LATEX_STANDARD_DEVIATION_SIDES_HEADERS = [
    r"$$s_a \space [mm]$$",
    r"$$s_b \space [mm]$$",
    r"$$s_c \space [mm]$$",
    r"$$s_{ha} \space [mm]$$",
    r"$$s_{hb} \space [mm]$$",
    r"$$s_{hc} \space [mm]$$",
]

LATEX_MEASUREMENT_HEADERS = [
    r"$$a \space [mm]$$",
    r"$$b \space [mm]$$",
    r"$$c \space [mm]$$",
    r"$$h_a \space [mm]$$",
    r"$$h_b \space [mm]$$",
    r"$$h_c \space [mm]$$",
]
LATEX_UNCERTAINTY_HEADERS = [
    r"$$u(\bar{a})$$",
    r"$$u(\bar{b})$$",
    r"$$u(\bar{c})$$",
    r"$$u( \bar{h_a})$$",
    r"$$u(\bar{h}_b)$$",
    r"$$u(\bar{h}_c)$$",
]
LATEX_STANDARD_UNCERTAINTY_HEADERS = [
    r"$$u(a)$$",
    r"$$u(b)$$",
    r"$$u(c)$$",
    r"$$u(h_a)$$",
    r"$$u(h_b)$$",
    r"$$u(h_c)$$",
]
LATEX_TRUST_INTERVALS_HEADERS = [
    r"$$a \space [mm]$$",
    r"$$b \space [mm]$$",
    r"$$c \space [mm]$$",
    r"$$h_a \space [mm]$$",
    r"$$h_b \space [mm]$$",
    r"$$h_c \space [mm]$$",
]
LATEX_AREA_HEADERS = [
    r"$$S_{heron} \space [mm^2]$$",
    r"$$S_{ah} \space [mm^2]$$",
    r"$$S_{bh} \space [mm^2]$$",
    r"$$S_{ch} \space [mm^2]$$",
]
LATEX_SURFACE_STANDARD_DEVIATIONS_HEADERS = [
    r"$$u(S_{heron}) \space [mm^2]$$",
    r"$$u(S_{ah}) \space [mm^2]$$",
    r"$$u(S_{bh}) \space [mm^2]$$",
    r"$$u(S_{ch}) \space [mm^2]$$",
]
LATEX_EXTENDED_UNCERTAINTIES_HEADERS = [
    r"$$S_{\bar{y}{Heron}}$$",
    r"$$S_{\bar{y}{ah}}$$",
    r"$$S_{\bar{y}{bh}}$$",
    r"$$S_{\bar{y}{ch}}$$",
]

LATEX_SURFACE_TRUST_INTERVALS_HEADERS = [
    r"$$S_{heron} \space [mm^2]$$",
    r"$$S_{ah} \space [mm^2]$$",
    r"$$S_{bh} \space [mm^2]$$",
    r"$$S_{ch} \space [mm^2]$$",
]


def mark_outliers(df: pd.DataFrame) -> pd.DataFrame:
    columns = df.columns.values.tolist()

    columns_absdiff = [f"absdiff({column})" for column in columns]

    thresholds = []
    all_means = []
    for column in columns:
        mean = df[column].mean()
        mean_col = []
        thresholds.append(3 * df[column].std())
        for line in df[column]:
            result = np.abs((line - mean))
            mean_col.append(result)
        all_means.append(mean_col)
        # print(mean_col)

    diff_df = pd.DataFrame(all_means)
    diff_df = diff_df.T
    diff_df.columns = columns_absdiff

    # wykrywanie błędów grubych
    # Tworzenie funkcji do określania koloru komórki na podstawie wartości granicznej
    def color_cell(value, threshold):
        if abs(value) < threshold:
            return "background-color: green"
        else:
            return "background-color: red"

    # Tworzenie kolorowego DataFrame
    return (
        diff_df.style.applymap(
            lambda x: color_cell(x, thresholds[0]),
            subset=pd.IndexSlice[:, columns_absdiff[0]],
        )
        .applymap(
            lambda x: color_cell(x, thresholds[1]),
            subset=pd.IndexSlice[:, columns_absdiff[1]],
        )
        .applymap(
            lambda x: color_cell(x, thresholds[2]),
            subset=pd.IndexSlice[:, columns_absdiff[2]],
        )
        .applymap(
            lambda x: color_cell(x, thresholds[3]),
            subset=pd.IndexSlice[:, columns_absdiff[3]],
        )
        .applymap(
            lambda x: color_cell(x, thresholds[4]),
            subset=pd.IndexSlice[:, columns_absdiff[4]],
        )
        .applymap(
            lambda x: color_cell(x, thresholds[5]),
            subset=pd.IndexSlice[:, columns_absdiff[5]],
        )
    )


def remove_outliers(df: pd.DataFrame) -> pd.DataFrame:
    # Calculate mean and standard deviation for each column
    means = df.mean()
    stds = df.std()

    # Identify rows where any value deviates more than 3 standard deviations
    mask = (np.abs(df - means) <= (3 * stds)).all(axis=1)

    # Return DataFrame without outliers
    return df.loc[mask]


def compute_column_means(df: pd.DataFrame) -> pd.DataFrame:
    # Compute the mean for each column
    column_means = df.mean().to_frame().T

    return column_means


def compute_standard_undertainty(df: pd.DataFrame) -> pd.DataFrame:
    # compute standard uncertainty for each column defined as standard deviation from the mean divided by the square root of the number of measurements
    column_std = df.std().to_frame().T
    return column_std


def compute_standard_measurement_uncertainty(
    df: pd.DataFrame, device_uncertainty: float
) -> pd.DataFrame:
    # compute uncertaining for eaach column defined as square root of the sum of the standard uncertainty squared and the device uncertainty squared
    column_std = compute_standard_undertainty(df)
    column_std = np.sqrt(column_std**2 + (device_uncertainty / np.sqrt(3)) ** 2)
    return column_std


def compute_extended_standard_uncertainty(df: pd.DataFrame) -> pd.DataFrame:
    # compute extended standard uncertainty for each column defined as the standard uncertainty multipied by t-distribution value for 97% confidence interval
    column_std = compute_standard_undertainty(df)
    column_std = column_std / np.sqrt(len(df)) * 3.7889823828484244
    return column_std


def compute_triangle_surface_heron_method(df: pd.DataFrame) -> pd.DataFrame:
    # Compute the surface of the triangle using the Heron's method
    a = df["a"]
    b = df["b"]
    c = df["c"]
    s = (a + b + c) / 2
    surface = np.sqrt(s * (s - a) * (s - b) * (s - c))

    return surface


def compute_triangle_surface_area(
    df: pd.DataFrame, side: str, height: str, descriptor: str
) -> pd.DataFrame:
    # Compute the surface of the triangle using the area formula
    a = df[side]
    h = df[height]
    surface = a * h / 2

    # return series with results
    return surface


def compute_triangle_surface_all_methods(df: pd.DataFrame) -> pd.DataFrame:
    # Compute the surface of the triangle using all methods and create new data frame with just sufraces
    surfaces = pd.DataFrame()
    surfaces["area_heron"] = compute_triangle_surface_heron_method(df)
    surfaces["area_ah"] = compute_triangle_surface_area(df, "a", "ha", "a")
    surfaces["area_bh"] = compute_triangle_surface_area(df, "b", "hb", "b")
    surfaces["area_ch"] = compute_triangle_surface_area(df, "c", "hc", "c")

    return surfaces


def compute_combined_standard_deviation(
    areas_df: pd.DataFrame, means_df: pd.DataFrame
) -> pd.DataFrame:
    """
    Compute the combined standard deviation for each row in the areas_df DataFrame.
    defined as sqrt(sum((area - mean)**2) / n(n-1)) and return dataframe with results
    """

    combined_std = np.sqrt(
        ((areas_df - means_df) ** 2).sum() / (len(areas_df) * (len(areas_df) - 1))
    )

    # Create a new DataFrame with one row
    result = pd.DataFrame([combined_std.values], columns=combined_std.index)
    return result
    # compute the combined standard deviation for each row
