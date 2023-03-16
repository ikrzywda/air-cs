from math import inf
from uncertainty import Uncertainty, DeviceUncertainty

BRYMEN_BM811_VOLTAGE = DeviceUncertainty(
    device_name="BrymenB811",
    probing_specs=[
        (50, Uncertainty(uncentainty=0.0012, lsd_magnitude=0.01, c_constant=2)),
        (500, Uncertainty(uncentainty=0.0006, lsd_magnitude=0.01, c_constant=2)),
    ],
)

BRYMEN_BM811_CURRENT = DeviceUncertainty(
    device_name="BrymenB811",
    probing_specs=[
        (inf, Uncertainty(uncentainty=0.0002, lsd_magnitude=0.0001, c_constant=4)),
    ],
)
