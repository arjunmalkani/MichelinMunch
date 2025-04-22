  # MichelinMunch

A C++ command‑line tool for discovering affordable Michelin‑rated restaurants using two custom hash‑map implementations (separate‑chaining & open‑addressing) and timing their performance.

## Features

- **Triple‑layered maps** by City → Star Rating → Price Level  
  – Built with  
  &nbsp;&nbsp;• Separate chaining (`HashMapChaining.h`)  
  &nbsp;&nbsp;• Open addressing (`HashMapOpen.h`)  
- **Dataset loader** (`DatasetLoader.h`):  
  • Parses CSV file dataset of 17,000+ Michelin restaurants
- **Interactive CLI**:  
  • Query by city, star count (1–3 or “Selected Restaurants”) and price ($–$$$$)  
  • Displays matching restaurants with name, address, cuisine
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
Following our proposal from Project 3a, our group had to make alterations to the initial plan. After realizing that hash maps would be a better implementation to service our project, we shifted our design goals to fit this new idea. This includes discussing the implementation of hash maps for our project, deciding the triple nested approach, and also deciding to compare separate chaining to open addressing. Therefore, we could use user inputs as keys and layer the maps as values until reaching the desired list of restaurants. After making this decision, we altered the distribution of roles for Anthony and Elizabeth, who were tasked with creating the sorting algorithms, by having them create the open addressed hash map and separate chaining hash map respectively.

Getting started with the coding required us to first facilitate an understanding of Git. We did so by creating our repository on GitHub, cloning the repositories to our local machine, and learning the different Git commands for the terminal and how to use them. Doing this was crucial for our collaborative efforts to be unanimously agreed upon and simple to approach. Lastly, once developing the basic foundations of our project through Git, we researched our assigned portions of the project and how to implement them in our project.

### Prerequisites

- C++17‑compatible compiler (e.g. `g++`, `clang++`)  
- CMake ≥ 3.10 (optional but recommended)  
- Git

### Clone the repo

```bash
git clone https://github.com/<your‑org>/MichelinMunch.git
cd MichelinMunch
