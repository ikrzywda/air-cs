import os
import sys
from typing import List

import pandas as pd


def normalize_formatting(input_path: str, output_path: str, header: List[str]):
    with open(input_path, "r") as file:
        input = file.read()
        line_list = input.splitlines()
        has_headers = line_list and line_list[0][0].isalpha()
        replaced_commas = input.replace(",", ".")
        sanitized = replaced_commas.replace(";", ",")

    with open(output_path, "w") as output_file:
        if not has_headers:
            output_file.write(header + "\n")
        output_file.write(sanitized)


def get_sample_data(df: pd.DataFrame, probing_count: int) -> pd.DataFrame:
    return df[df.index % probing_count == 0][5:15]


if __name__ == "__main__":
    input_dir, output_dir = sys.argv[1], sys.argv[2]
    paths = [os.path.join(input_dir, fn) for fn in next(os.walk(input_dir))[2]]
    for input_file in paths:
        # print(os.path.join(output_dir, os.path.basename(input_file)))
        normalize_formatting(
            input_file,
            os.path.join(output_dir, os.path.basename(input_file)),
            header="U,I",
        )
