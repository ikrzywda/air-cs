import numpy as np
import pandas as pd
from pydantic import BaseModel
from sklearn.linear_model import LinearRegression
from matplotlib import pyplot as plt
from typing import Tuple


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
