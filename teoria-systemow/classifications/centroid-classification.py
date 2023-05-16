import math
from typing import Dict

from data import TRAINING_DATA, TEST_DATA


def calculate_distance(point1, point2):
    # Calculate Euclidean distance between two points
    distance = math.sqrt(sum([(a - b) ** 2 for a, b in zip(point1, point2)]))
    return distance


def compute_centroids(training_data) -> Dict[float, float]:
    centroids = {key: [] for key in set([point[-1] for point in training_data])}

    for point in training_data:
        centroids[point[-1]].append(point[:-1])

    return {key: [sum(x) / len(x) for x in zip(*centroids[key])] for key in centroids}


def nearest_centroid(training_data, test_point):
    min_distance = float("inf")
    nearest_class = None

    centroids = compute_centroids(training_data)

    for key in centroids:
        distance = calculate_distance(centroids[key], test_point)
        if distance < min_distance:
            min_distance = distance
            nearest_class = key

    return nearest_class


def classify_centroid(training_data, test_data):
    classes = []

    for test_point in test_data:
        nearest_class = nearest_centroid(training_data, test_point)
        classes.append(nearest_class)

    return classes


print(classify_centroid(TRAINING_DATA, TEST_DATA))
