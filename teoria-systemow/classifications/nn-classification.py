import math
from .data import TRAINING_DATA, TEST_DATA


def calculate_distance(point1, point2):
    # Calculate Euclidean distance between two points
    distance = math.sqrt(sum([(a - b) ** 2 for a, b in zip(point1, point2)]))
    return distance


def nearest_neighbor(training_data, test_point):
    min_distance = float("inf")
    nearest_class = None

    for point in training_data:
        distance = calculate_distance(point[:-1], test_point)
        if distance < min_distance:
            min_distance = distance
            nearest_class = point[-1]

    return nearest_class


def classify_nn(training_data, test_data):
    classes = []

    for test_point in test_data:
        nearest_class = nearest_neighbor(training_data, test_point)
        classes.append(nearest_class)

    return classes


print(classify_nn(TRAINING_DATA, TEST_DATA))
