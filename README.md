# OOP Lab Final Project - Kingdom Simulation

## Group Members

- **Mian Dawood bin Rafay** (24F-3053)
- **Zain** (24F-3083)

## Project Overview

This project simulates the management and governance of a medieval kingdom. Players are tasked with overseeing various aspects of the kingdom, including its population, military, economy, resources, and leadership. The goal is to maintain stability within the kingdom by making strategic decisions related to taxation, trade, military management, and handling events such as famine, war, or corruption.

## Project Structure

The project is divided into several classes, each managing a different aspect of the kingdom:

### Mian Dawood's Responsibilities:
1. **Population**: Manages the population of the kingdom, including various social classes (Peasants, Merchants, Nobles, Soldiers), their growth, happiness, and health.
2. **Resource**: Handles resources like food, wood, stone, iron, and gold. Manages their gathering, consumption, and trade.
3. **Economy**: Handles the economic structure, taxation, inflation, and public services funding.
4. **Military**: Manages military units, training, pay, and morale.
5. **EventManager**: Manages random events like famine, disease, and war, which affect the kingdom's stability.
6. **Audit**: Conducts audits to monitor and ensure the financial health of the kingdom, detecting fraud and mismanagement.

### Zain's Responsibilities:
1. **Bank**: Manages banking functionality, including loans, interest, and fraud detection.
2. **Leadership**: Manages the kingdom's leadership, including different leadership styles (autocratic, democratic), popularity, elections, and coups.
3. **ResourceManager**: Oversees resource collection, stockpiling, and trade.
4. **Corruption**: Manages corruption levels in the kingdom, influencing various systems like economy, military, and leadership.
5. **Event**: Represents specific events (e.g., famine, war, drought) and their impact on the kingdom.
6. **Kingdom**: Acts as the main container class that ties together all the components of the kingdom.

## Features

- **Population Management**: Simulate the growth and decline of different social classes based on various factors.
- **Leadership**: Simulate different leadership styles and their impact on the kingdom’s popularity and stability.
- **Economy**: Handle taxation, inflation, and trade to balance the kingdom's finances.
- **Military**: Manage military training, pay, and morale to defend the kingdom from external threats.
- **Resources**: Track and manage resources like food, wood, stone, and gold, essential for the kingdom's survival and expansion.
- **Events**: Random events can emerge, such as famine, disease, or war, which must be managed by the leadership.
- **Banking System**: Loans, interest, and fraud detection, all affecting the kingdom's economy.
- **Corruption**: Monitor and manage corruption within the kingdom’s systems.

## Technologies Used

- C++: Object-Oriented Programming for creating the game simulation.
- Git & GitHub: Version control and code management.
- Visual Studio Code: IDE for writing and managing the code.

## Project Division

### Mian Dawood's Tasks:
- Implemented **Stronghold.h**, **Resource.cpp**, **Population.cpp**, **Economy.cpp**, **Military.cpp**, **EventManager.cpp**, and **Audit.cpp** classes.
- Designed and implemented the core game mechanics related to kingdom management.

### Zain's Tasks:
- Implemented **Bank.cpp**, **Leadership.cpp**, **Resource.cpp**, **ResourceManager.cpp**, **Corruption.cpp**, **Event.cpp**, and **Kingdom.cpp** classes.
- Managed the integration of all the systems and ensured smooth interactions between different components.

## How to Run the Project

1. Clone this repository using `git clone <repository-link>`.
2. Open the project folder in a C++ compatible IDE (e.g., Visual Studio Code).
3. Build the project using the IDE's build tools.
4. Run the executable to start the kingdom simulation game.