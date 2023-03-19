from math import inf
from uncertainty import Uncertainty, DeviceUncertainty


BRYMEN_BM811_VOLTAGE = DeviceUncertainty(
    device_name="BrymenB811",
    probing_specs=[
        (50, Uncertainty(uncertainty=0.0012, lsd_magnitude=1, c_constant=2)),
        (500, Uncertainty(uncertainty=0.0006, lsd_magnitude=1, c_constant=2)),
    ],
)

BRYMEN_BM811_CURRENT = DeviceUncertainty(
    device_name="BrymenB811",
    probing_specs=[
        (inf, Uncertainty(uncertainty=0.002, lsd_magnitude=0.01, c_constant=4)),
        (inf, Uncertainty(uncertainty=0.002, lsd_magnitude=0.01, c_constant=4)),
    ],
)
