from functools import reduce
from typing import Any

import numpy as np


def m_standard_deviation(x_vec: np.array) -> np.floating[Any]:
    mean = np.mean(x_vec)
    return np.sqrt(np.mean([(mean - x) ** 2 for x in x_vec]))


def m_covariance(x_vec: np.array, y_vec: np.array) -> np.floating[Any]:
    x_mean = np.mean(x_vec)
    y_mean = np.mean(y_vec)

    difference_products = np.array(
        [(x_mean - x) * (y_mean - y) for x, y in zip(x_vec, y_vec)]
    )
    return np.mean(difference_products)


def m_correlation(x_vec: np.array, y_vec: np.array) -> np.floating[Any]:
    return m_covariance(x_vec, y_vec) / (
        m_standard_deviation(x_vec) * m_standard_deviation(y_vec)
    )


def m_autocovariance(x_vec: np.array, lag: int) -> np.floating[Any]:
    lagged_x_vec = np.roll(x_vec, lag)
    return m_covariance(x_vec, lagged_x_vec)


def m_autocorrelation(x_vec: np.array, lag: int) -> np.floating[Any]:
    autocovariance = m_autocovariance(x_vec, lag)
    return autocovariance / m_autocovariance(x_vec, 0)


def m_cross_correlation(x_vec: np.array) -> np.array:
    result = np.zeros(len(x_vec))
    for m in range(1, len(x_vec) + 1):
        rolled_arr = np.roll(x_vec, m)
        for n in range(m):
            result[m - 1] += rolled_arr[n] * x_vec[n]

    return np.append(result, np.flip(result)[1:])


def run_comparison_with_numpy(x_vec: np.array, y_vec: np.array, prompt: str) -> None:
    print(prompt)
    print("my covariance: ", m_covariance(x_vec, y_vec))
    print("numpy covariance: ", np.cov(x_vec, y_vec)[0][1])

    print("my standard deviation", m_standard_deviation(x_vec))
    print("numpy standard deviation", np.std(x_vec))

    print("my correlation: ", m_correlation(x_vec, y_vec))
    print("numpy correlation: ", np.corrcoef(x_vec, y_vec)[0][1])

    print("my autocovariance: ", m_autocovariance(x_vec, 0))
    print("numpy autocovariance: ", np.cov(x_vec, np.roll(x_vec, 1))[0][1])

    print("my autocorrelation: ", m_autocorrelation(x_vec, 1))
    print("numpy autocorrelation: ", np.corrcoef(x_vec, np.roll(x_vec, 1))[0][1])

    print("=========================================")


if __name__ == "__main__":
    random_x = np.random.randint(0, 100, 100)
    random_y = np.random.randint(0, 100, 100)

    sin_x = np.sin(np.linspace(0, 2 * np.pi, 100))
    cos_x = np.cos(np.linspace(0, 2 * np.pi, 100))
    sin_x_with_offset = np.sin(np.linspace(0, 2 * np.pi, 100)) + 1
    linear_x_with_positive_coefficient = np.linspace(0, 100, 100)
    linear_x_with_negative_coefficient = np.linspace(100, 0, 100)

    run_comparison_with_numpy(random_x, random_y, "random x and y")
    run_comparison_with_numpy(sin_x, cos_x, "sin x and cos x")
    run_comparison_with_numpy(sin_x, sin_x_with_offset, "sin x and sin x with offset")
    run_comparison_with_numpy(sin_x, sin_x, "sin x and sin x")
    run_comparison_with_numpy(
        linear_x_with_positive_coefficient,
        linear_x_with_negative_coefficient,
        "linear x with positive coefficient and linear x with negative coefficient",
    )

    x_vec = np.array([1, 2, 3, 4, 5])
    print("my cross correlation: ", m_cross_correlation(x_vec))
    print("numpy cross correlation: ", np.correlate(x_vec, x_vec, mode="full"))
