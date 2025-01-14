import matplotlib.pyplot as plt
import numpy as np
import math

def plot_robotic_arm(theta_0, theta_1, theta_2, x, y):
    # Convert angles from degrees to radians
    theta_0 = np.radians(theta_0)
    theta_1 = np.radians(theta_1)
    theta_2 = np.radians(theta_2)

    # Calculate joint positions
    joint_1_x = x * np.cos(theta_0)
    joint_1_y = x * np.sin(theta_0)

    joint_2_x = joint_1_x + y * np.cos(theta_0 + theta_1)
    joint_2_y = joint_1_y + y * np.sin(theta_0 + theta_1)

    claw_x = joint_2_x + y * np.cos(theta_0 + theta_1 + theta_2)
    claw_y = joint_2_y + y * np.sin(theta_0 + theta_1 + theta_2)

    # Plot the arm
    plt.figure(figsize=(6, 6))
    plt.plot([0, joint_1_x, joint_2_x, claw_x], [0, joint_1_y, joint_2_y, claw_y], marker='o', lw=2)  # Arm segments

    # Annotate points
    plt.text(0, 0, "Base", fontsize=10, ha='right')
    plt.text(joint_1_x, joint_1_y, "Joint 1", fontsize=10, ha='left')
    plt.text(joint_2_x, joint_2_y, "Joint 2", fontsize=10, ha='left')
    plt.text(claw_x, claw_y, "Claw", fontsize=10, ha='left')

    # Set plot limits and labels
    max_range = x + y + 5
    plt.xlim(-max_range, max_range)
    plt.ylim(-max_range, max_range)
    plt.axhline(0, color='black', lw=0.5, ls='--')
    plt.axvline(0, color='black', lw=0.5, ls='--')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.title("2D Robotic Arm Visualization")
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.grid(True)
    plt.show()
    
def calculate_inverse_kinematics(B, R, target_x):
    # Calculate the total distance from the base to the target
    D = target_x
    
    # Check if the point is reachable
    if D > B + R or D < abs(B - R):
        print("Target out of reach!")
        return None, None
    
    # Calculate theta_2 using the Law of Cosines
    cos_theta_2 = (B**2 + R**2 - D**2) / (2 * B * R)
    theta_2 = math.acos(cos_theta_2)  # In radians
    
    # Calculate theta_1 using atan2
    theta_1 = math.atan2(R * math.sin(theta_2), B + R * math.cos(theta_2))
    
    # Convert to degrees for convenience
    theta_1_deg = math.degrees(theta_1)
    theta_2_deg = math.degrees(theta_2)
    
    return theta_1_deg, theta_2_deg

# Example usage
if __name__ == "__main__":
    # Arm parameters
    theta_0 = 30  # Base angle in degrees
    theta_1 = 45  # First arm angle in degrees
    theta_2 = 60  # Second arm angle in degrees
    B = 10        # Length of the first arm
    R = 5         # Length of the second arm
    target_x = B + 1

    theta_1, theta_2 = calculate_inverse_kinematics(B, R, target_x)
    if theta_1 is not None:
        print(f"To reach ({target_x}, 0):")
        print(f"Theta 1: {theta_1:.2f} degrees")
        print(f"Theta 2: {theta_2:.2f} degrees")

    # Visualize the robotic arm
    plot_robotic_arm(theta_0, theta_1, theta_2, B, R)
