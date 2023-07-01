from unittest import result
import numpy as np
import pandas as pd
from pydantic import BaseModel
from sklearn.linear_model import LinearRegression
from matplotlib import pyplot as plt
from typing import Tuple
import statsmodels.api as sm
from math import sqrt


class LinearRegressionData(BaseModel):
    a: float
    b: float


def get_regression(
    x: np.ndarray, y: np.ndarray
) -> Tuple[LinearRegressionData, np.ndarray, LinearRegression]:
    _x = x.reshape(len(x), 1)
    _y = y.reshape(len(y), 1)

    regression_model = LinearRegression().fit(_x, _y)
    regression_model.score(_x, _y)

    return (
        LinearRegressionData(
            a=regression_model.coef_[0], b=regression_model.intercept_
        ),
        _x,
        regression_model,
    )


def get_regression_summary(x: np.ndarray, y: np.ndarray):
    x = sm.add_constant(x)
    model = sm.OLS(y, x)
    results = model.fit()

    a = results.params[1]
    b = results.params[0]
    ua = results.bse[1]
    ub = results.bse[0]

    print("a: ", results.params[1])
    print("b: ", results.params[0])
    print("vbi: ", -b / a)
    print("uvbi", sqrt((b / (a**2) * ua) ** 2 + (1 / a * ub) ** 2))
    print("rz: ", 1 / a, ua / a**2)
    print("uuz: ", 1 / ua)
