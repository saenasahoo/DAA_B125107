# Fair vs Biased Coin Toss Simulation

This question uses simulation in C to demonstrate the difference between a fair coin and a biased coin.

## Problem Statement

A fair coin has an equal probability of producing HEAD or TAIL:

```text
P(HEAD) = 0.5
P(TAIL) = 0.5
```

The task is to extend the simulation to a biased coin and compare the experimental results with the expected probabilities.

For a biased coin in this experiment:

```text
P(HEAD) = 0.75
P(TAIL) = 0.25
```

The simulation performs a large number of coin tosses and observes how closely the experimental probabilities approach the theoretical probabilities.

## Approach

1. Generate random coin tosses using C.
2. Simulate a large number of tosses.
3. Count the number of HEAD and TAIL outcomes.
4. Calculate the experimental probability of each outcome.
5. Repeat the experiment for the biased coin.
6. Store the results in a CSV file.
7. Plot the results to compare the observed probabilities with the expected probabilities.

## Expected Probability

For a fair coin:

| Outcome | Expected Probability |
|---|---:|
| HEAD | 0.50 |
| TAIL | 0.50 |

For the biased coin:

| Outcome | Expected Probability |
|---|---:|
| HEAD | 0.75 |
| TAIL | 0.25 |

## Folder Structure

```text
Q2/
├── coin_toss.c
├── coin_toss.csv
├── coin_toss_plot.png
├── plot_coin_toss.py
└── README.md
```

## Files Description

- `coin_toss.c` – C program that performs the fair and biased coin-toss simulations.
- `coin_toss.csv` – Contains the experimental simulation results.
- `coin_toss_plot.png` – Graph comparing the experimental and theoretical probabilities.
- `plot_coin_toss.py` – Python script used to generate the plot.
- `README.md` – Documentation for Question 2.

## Objective

The objective is to understand how simulation can be used to estimate probabilities and to observe how the experimental probability approaches the theoretical probability as the number of trials increases.

## Result

The simulation shows that for a sufficiently large number of tosses, the experimental probability approaches the expected probability.

For the fair coin, the proportion of HEAD outcomes approaches 0.5.

For the biased coin, the proportion of HEAD outcomes approaches 0.75.

## Conclusion

The experiment demonstrates that repeated random trials can be used to estimate probability. As the number of coin tosses increases, the experimental results generally become closer to the theoretical probabilities.
