import random

# Define the initial probabilities
initial_probabilities = [50,50,1]
alpha = 1  # You can change alpha to 0.5 or other values for testing

# Function to select an outcome based on current probabilities
def select_outcome(probabilities):
    return random.choices(range(len(probabilities)), probabilities)[0]

# Function to update probabilities based on the selected outcome using squared initial probabilities
# and distribute the probabilities among all outcomes including the selected one with alpha = 1
def update_probabilities_all(probabilities, selected_outcome, initial_probabilities):
    selected_prob = probabilities[selected_outcome]
    
    new_probabilities = probabilities.copy()
    new_probabilities[selected_outcome] = 0  # Set the selected outcome probability to zero
    
    delta_p = selected_prob
    squared_initial_probs = [p**2 for p in initial_probabilities]
    sum_squared_probs = sum(squared_initial_probs)
    
    for i in range(len(probabilities)):
        new_probabilities[i] += (squared_initial_probs[i] / sum_squared_probs) * delta_p
    
    return new_probabilities

# Simulate the process
num_simulations = 80  # You can change this value for testing
current_probabilities = initial_probabilities.copy()
results = []

for _ in range(num_simulations):
    outcome = select_outcome(current_probabilities)
    results.append(outcome)
    current_probabilities = update_probabilities_all(current_probabilities, outcome, initial_probabilities)

# Calculate the real frequencies
real_frequencies = {i: results.count(i) / num_simulations for i in range(len(initial_probabilities))}

# Output the results
print(f"Total simulations: {num_simulations}")
print("Index | Initial Probability | Real Frequency | Current Probability")
for i in range(len(initial_probabilities)):
    current_prob = current_probabilities[i]
    print(f"{i}     | {initial_probabilities[i]:>17}     | {real_frequencies[i]:>13.4f}   | {current_prob:>18.4f}")
