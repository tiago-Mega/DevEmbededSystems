# Software Defined Vehicle (SDV) Platform

## Project Information

**Project Name:** Software Defined Vehicle Platform

**Degree:** MSc Electrical and Computer Engineering

**Status:** Planning

**Version:** 0.1

---

# Vision

Design and implement a miniature Software Defined Vehicle (SDV) platform that demonstrates the transition from traditional distributed Electronic Control Units (ECUs) toward centralized automotive computing.

The project should emphasize:

- Embedded Systems Engineering
- Automotive Networking
- Real-Time Systems
- Embedded Linux
- Software Architecture
- AUTOSAR-inspired design
- Diagnostics
- Gateway development

The system should be modular and expandable throughout the duration of the master's project.

---

# Long-Term Objectives

Develop practical experience with

- Embedded C
- Modern C++
- STM32
- ARM Cortex-M
- FreeRTOS
- Raspberry Pi
- Linux
- CAN
- CAN FD
- Automotive Ethernet
- TCP/IP
- UDS
- ISO-TP
- SocketCAN
- AUTOSAR concepts
- Embedded debugging
- System integration

---

# Research Goal

Investigate modern Software Defined Vehicle architectures.

Possible research topics include:

- Gateway latency
- CAN versus Ethernet communication
- Centralized computing
- ECU scalability
- Network utilization
- Fault tolerance
- Modular software architectures

These research questions may evolve during the project.

---

# Current System Architecture

Laptop

↓

Diagnostics GUI

↓

Ethernet

↓

Raspberry Pi

↓

CAN Gateway

↓

CAN Network

↓

STM32 ECUs

---

# Planned ECUs

## Body Control Module

Responsibilities

- Doors
- Windows
- Interior Lighting
- Hazard Lights

---

## Instrument Cluster

Responsibilities

- Dashboard Display
- Warning Indicators
- Vehicle Status

---

## HVAC ECU

Responsibilities

- Cabin Temperature
- Fan Speed
- Climate Simulation

---

## Battery ECU

Responsibilities

- Voltage
- Current
- Temperature
- State of Charge

---

## Future ECUs

Potential additions

- ABS
- Steering
- Infotainment
- ADAS
- Engine Simulator

---

# Networking

Primary vehicle network

CAN

Future support

- CAN FD
- Automotive Ethernet
- SOME/IP

Diagnostics

- UDS
- ISO-TP

Gateway

CAN ↔ Ethernet

---

# Embedded Software

Microcontrollers

STM32

Language

C17

Operating System

FreeRTOS

Architecture

Application

↓

Services

↓

Communication

↓

Drivers

↓

HAL

---

# Raspberry Pi

Operating System

Linux

Languages

- Python
- C++

Responsibilities

- Gateway
- Diagnostics
- OTA
- Logging
- Visualization

---

# Design Principles

The project should prioritize

- Modularity
- Simplicity
- Maintainability
- Testability
- Documentation
- Reusability

---

# Coding Standards

Embedded

- Prefer static allocation
- Avoid recursion
- Avoid dynamic allocation
- Keep ISRs short
- Separate hardware abstraction

Linux

- Modular applications
- Modern C++ where appropriate
- Python for tooling

---

# Testing Strategy

Every subsystem should include

- Unit testing
- Integration testing
- Latency testing
- Stress testing
- Fault injection
- Recovery testing

---

# Documentation

Every module should include

- Purpose
- Interfaces
- Dependencies
- Communication
- Configuration
- Limitations
- Future Improvements

---

# Milestones

## Phase 1

Research

Architecture

Hardware selection

---

## Phase 2

CAN communication

STM32 firmware

Basic ECU implementation

---

## Phase 3

Gateway

Linux

Ethernet

Diagnostics

---

## Phase 4

OTA

System integration

Performance optimization

---

## Phase 5

Evaluation

Benchmarking

Research experiments

---

## Phase 6

Thesis writing

Presentation

Final validation

---

# Stretch Goals

- AUTOSAR-like RTE
- CAN FD
- SOME/IP
- Automotive Ethernet
- Secure Boot
- Intrusion Detection System
- TinyML
- Qt Dashboard

---

# Repository Structure

/docs

/firmware

/gateway

/tests

/hardware

/scripts

/tools

/thesis

---

# Current Sprint

(To be updated weekly.)

Current focus:

- None

Next milestone:

- Finalize hardware selection

Current blockers:

- None

---

# Notes

This document is intended to evolve throughout the project.

It should always represent the current state of the system.