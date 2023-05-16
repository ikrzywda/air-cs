import math
from .data import TRAINING_DATA, TEST_DATA


def calculate_distance(point1, point2):
    # Calculate Euclidean distance between two points
    distance = math.sqrt(sum([(a - b) ** 2 for a, b in zip(point1, point2)]))
    return distance


def nearest_neighbor(training_data, test_point, k=3):
    training_data_with_distances = [
        [*point, calculate_distance(point[:-1], test_point)] for point in training_data
    ]
    sorted_training_data = sorted(training_data_with_distances, key=lambda x: x[-1])
    return sorted_training_data[:k]


def classify_knn(training_data, test_data, k=3):
    classes = []

    for test_point in test_data:
        nearest_classes = nearest_neighbor(training_data, test_point, k)
        nearest_classes = [point[-2] for point in nearest_classes]
        classes.append(max(set(nearest_classes), key=nearest_classes.count))

    return classes


print(classify_knn(TRAINING_DATA, TEST_DATA))
