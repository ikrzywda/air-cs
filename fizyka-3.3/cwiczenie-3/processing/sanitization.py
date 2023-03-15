from io import StringIO
import os
import sys
from typing import List
from attr import has

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

# def sort_inputs(input_str: str) -> str:
#     dataframe = pd.read_csv(StringIO(input_str))
#     dataframe.sort_values("U")
#     return dataframe.to_csv()


if __name__ == "__main__":
    input_dir = sys.argv[1]
    paths = [os.path.join(input_dir, fn) for fn in next(os.walk(input_dir))[2]]
    for input_file in paths:
        normalize_formatting(input_file, input_file.split(".")[0] + "-sanitized.csv", header="U,I")




