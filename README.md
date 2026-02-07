# Terminal Ballistic Simulator & Urban Environment Analyzer

A high-performance C++ simulation suite designed to model projectile trajectories in 3D space, featuring a Python-based visualizer for terminal ballistic analysis within a procedurally generated urban environment.

## Overview

The system is split into two main components:

    The Engine (C++): A physics simulator that calculates 3D trajectories and impacts, exporting results to trajectory.csv and landings.csv.

    The Visualizer (Python): A Plotly-powered tool that renders the simulation data in a 3D "Military Radar" style, complete with a procedurally generated city and target zones.

Core Features

    3D Vector Physics: High-accuracy trajectory calculation using a custom Vector3D class.

    Environmental Modeling: Modular Environment and Projectile classes for extensible physics (drag, wind, gravity).

    Procedural Urban Rendering: The Python visualizer generates a unique city layout for every run to contextualize impact data.

    High-Performance Exports: Optimized data handling for large-scale simulation batches.

## File Structure
### File	Description
mainSim.cpp	Entry point for the physics simulation.

Projectile.hpp/cpp	Defines projectile properties and state updates.

Environment.hpp/cpp	Handles physical constants and external forces.

Vector3D.hpp/cpp	Linear algebra utilities for 3D kinematics.

plotter.py	Generates the interactive 3D HTML report.

*.csv	Data exchange format between C++ and Python.

## Getting Started
### Prerequisites

For the Simulation (C++):

    C++17 compatible compiler (GCC/Clang/MSVC)

    Standard Library

For the Visualizer (Python):
Bash

pip install pandas plotly numpy

Usage

    Compile and Run the Simulator:
    Bash

    g++ -O3 mainSim.cpp Projectile.cpp Environment.cpp Vector3D.cpp -o sim_engine
    ./sim_engine

    Generate the Visual Report:
    Bash

    python3 plotter.py

    View Results: Open simulation_ville.html in your browser.

## 🚧 Current Status & Roadmap

This project is actively under development. I am currently refining the core engine and will be integrating new ideas and features as the simulation evolves.

Current Focus:

    Physics Fidelity: Improving physical constraints and adding environmental variables (e.g., dynamic air density, Magnus effect).

    Feature Iteration: Experimenting with new architectural patterns in C++ to optimize the HFT-style data pipeline.

    Constraint Discovery: Identifying and fixing edge-case physical behaviors during high-velocity flight phases.

    [!NOTE] As I discover more complex physical constraints or interesting mechanics, I will be updating the codebase to reflect higher-accuracy ballistic modeling.
