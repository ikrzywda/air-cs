import sim_preparation
import typer


app = typer.Typer()


@app.command()
def generate_simulation_script(
    simulation: sim_preparation.Simulation,
    config_path: str,
    output_path: str,
):
    sim_preparation.generate_matlab(simulation, config_path, output_path)


if __name__ == "__main__":
    app()
