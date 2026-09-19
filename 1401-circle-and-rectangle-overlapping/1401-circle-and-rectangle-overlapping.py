class Solution:
    def checkOverlap(self, radius: int, xCenter: int, yCenter: int,
                     x1: int, y1: int, x2: int, y2: int) -> bool:

        # Find the closest point in the rectangle
        # to the circle's center

        closest_x = max(x1, min(xCenter, x2))
        closest_y = max(y1, min(yCenter, y2))

        # Calculate squared distance
        dx = closest_x - xCenter
        dy = closest_y - yCenter

        distance_squared = dx * dx + dy * dy

        # Check if the point lies inside or on the circle
        return distance_squared <= radius * radius
        