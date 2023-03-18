import pandas as pd
from sigfig import round
import subprocess
from tabulate import tabulate
import re


def dataframe_to_latex_table(df: pd.DataFrame) -> str:
    delims = "".join(["l|" for i in range(len(df.columns))])
    delims = "{|" + delims + "}"

    headers = df.columns.tolist()
    latex_tab = tabulate(
        df,
        headers=headers,
        tablefmt="latex_booktabs",
        showindex=False,
        numalign="center",
    )

    latex_tab = re.sub(
        r"^\\begin{tabular}.*$",
        r"\\begin{table}[H]\\centering \n \\begin{tabular}" + f"{delims}",
        latex_tab,
        flags=re.MULTILINE,
    )
    latex_tab = re.sub(
        r"^\\end{tabular}.*$",
        r"\\end{tabular}\n\\end{table}",
        latex_tab,
        flags=re.MULTILINE,
    )
    latex_tab = latex_tab.replace("\\toprule", "\\hline\n \\rowcolor[HTML]{EFEFEF} ")
    latex_tab = latex_tab.replace("\\midrule", "")
    latex_tab = latex_tab.replace("\\bottomrule", "")
    latex_tab = latex_tab.replace("\\\\", "\\\\ \\hline")

    return latex_tab
