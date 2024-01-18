from scipy.optimize import fsolve


# Define the system of nominal_values_equations
def nominal_values_equations(variables, *args):
    f_k, k0, ks1, ks2 = variables
    Pk, c_pp, T_w1, T_zew, T_kz, T_w2 = args

    eq1 = Pk - c_pp * f_k * (T_kz - T_w1)
    eq2 = ks1 - ((0.7 * Pk) / (T_w1 - T_zew))
    eq3 = k0 - (
        (c_pp * f_k * T_kz - c_pp * f_k * T_w1 - ks1 * (T_w1 - T_zew)) / (T_w1 - T_w2)
    )
    eq4 = ks2 - (k0 * (T_w1 - T_w2) + c_pp * f_k * T_w1 - c_pp * f_k * T_w2) / (
        T_w2 - T_zew
    )

    return [eq1, eq2, eq3, eq4]


def initial_conditions_equations(variables, *args):
    T_w1, T_w2 = variables
    c_pp, f_k, T_zew, T_kz, k0, ks1, ks2 = args
    eq1 = c_pp * f_k * (T_kz - T_w1) - ks1 * (T_w1 - T_zew) - k0 * (T_w1 - T_w2)
    eq2 = k0 * (T_w1 - T_w2) + c_pp * f_k * (T_w1 - T_w2) - ks2 * (T_w2 - T_zew)

    return [eq1, eq2]


def solve_nominal_values(*args) -> tuple[float, float, float, float]:
    Pk, c_pp, T_w1, T_zew, T_kz, T_w2 = args
    nominal_values_initial_guess = [0, 0, 0, 0]
    nominal_values_result = fsolve(
        nominal_values_equations,
        nominal_values_initial_guess,
        args=(Pk, c_pp, T_w1, T_zew, T_kz, T_w2),
    )

    fk_solution, k0_solution, ks1_solution, ks2_solution = nominal_values_result
    return fk_solution, k0_solution, ks1_solution, ks2_solution


def solve_initial_conditions(*args) -> tuple[float, float]:
    c_pp, f_k, T_zew, T_kz, k0, ks1, ks2 = args
    initial_values_initial_guess = [0, 0]
    initial_values_result = fsolve(
        initial_conditions_equations,
        initial_values_initial_guess,
        args=(c_pp, f_k, T_zew, T_kz, k0, ks1, ks2),
    )

    T_w1_solution, T_w2_solution = initial_values_result
    return T_w1_solution, T_w2_solution


if __name__ == "__main__":
    # Provide initial guesses for the variables
    nominal_values_initial_guess = [0, 0, 0, 0]

    # Specify the values for the parameters
    Pk_val = 20_000
    c_pp_val = 1_000 * 1.2
    T_w1_val = 20.0
    T_zew_val = -20.0
    T_kz_val = 30.0
    T_w2_val = 15.0
    Cv1_val = 0.0
    Cv2_val = 0.0

    # Solve the system of nominal_values_equations
    result = fsolve(
        nominal_values_equations,
        nominal_values_initial_guess,
        args=(Pk_val, c_pp_val, T_w1_val, T_zew_val, T_kz_val, T_w2_val),
    )

    # Extract the solution
    fk_solution, k0_solution, ks1_solution, ks2_solution = result

    # Print the results
    print(f"fkN = {fk_solution};")
    print(f"k0N = {k0_solution};")
    print(f"ks1N = {ks1_solution};")
    print(f"ks2N = {ks2_solution};")

    initial_values_initial_guess = [0, 0]
    initial_values_result = fsolve(
        initial_conditions_equations,
        initial_values_initial_guess,
        args=(
            c_pp_val,
            fk_solution,
            T_zew_val,
            T_kz_val,
            k0_solution,
            ks1_solution,
            ks2_solution,
        ),
    )

    T_w1_solution, T_w2_solution = initial_values_result
    print(f"T_w1N = {T_w1_solution};")
    print(f"T_w2N = {T_w2_solution};")

    print(
        solve_nominal_values(Pk_val, c_pp_val, T_w1_val, T_zew_val, T_kz_val, T_w2_val)
    )

    print(
        solve_initial_conditions(
            c_pp_val,
            fk_solution,
            T_zew_val,
            T_kz_val,
            k0_solution,
            ks1_solution,
            ks2_solution,
        )
    )
