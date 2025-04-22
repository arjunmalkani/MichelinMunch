# MichelinMunch

A C++ command‑line tool for discovering affordable Michelin‑rated restaurants using two custom hash‑map implementations (separate‑chaining & open‑addressing) and timing their performance.

## Features

- **Triple‑layered maps** by City → Star Rating → Price Level  
  – Built with  
  &nbsp;&nbsp;• Separate chaining (`HashMapChaining.h`)  
  &nbsp;&nbsp;• Open addressing (`HashMapOpen.h`)  
- **Dataset loader** (`DatasetLoader.h`):  
  • Parses a CSV of 17,000+ Michelin entries, normalizes prices to `$…$$$$`  
- **Interactive CLI**:  
  • Query by city, star count (1–3 or “Selected Restaurants”) and price ($–$$$$)  
  • Displays matching restaurants with name, address, cuisine, website & phone  
- **Performance metrics**:  
  • Measures and prints insertion & lookup times (ms) for both map types

## Table of Contents

- [Getting Started](#getting-started)  
- [Building](#building)  
- [Usage](#usage)  
- [Dataset](#dataset)  
- [Project Structure](#project-structure)  
- [Contributing](#contributing)  
- [License](#license)

---

## Getting Started

### Prerequisites

- C++17‑compatible compiler (e.g. `g++`, `clang++`)  
- CMake ≥ 3.10 (optional but recommended)  
- Git

### Clone the repo

```bash
git clone https://github.com/<your‑org>/MichelinMunch.git
cd MichelinMunch
