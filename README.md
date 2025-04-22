  # MichelinMunch
  **UF COP3530 Project 3 by Anthony Perez, Arjun Malkani, and Elizabeth Gonzalez**

A C++ CLI based program for discovering affordable Michelin‑rated restaurants using two custom hash‑map implementations (separate‑chaining & open‑addressing) and timing their performance to see which has better results.

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
    -[Shifting Our Design](#shifting-our-design)
    - [Step 1: Create Your Project Repository](#step-1-create-your-project-repository)
		- [Step 2: Repository Name and Visibility](#step-2-repository-name-and-visibility)
		- [Step 3: Collaboration and Team Members](#step-3-collaboration-and-team-members)
		- [Step 4: Development](#step-4-development)

- [Building](#building)  
- [Usage](#usage)  
- [Dataset](#dataset)  
- [Project Structure](#project-structure)  
- [Contributing](#contributing)  
- [License](#license)

  - [Documentation and resources on how to use GitHub for Project 3](#documentation-and-resources-on-how-to-use-github-for-project-3)
	- [Getting Started with the Project](#getting-started-with-the-project)
		- [Step 1: Create Your Project Repository](#step-1-create-your-project-repository)
		- [Step 2: Repository Name and Visibility](#step-2-repository-name-and-visibility)
		- [Step 3: Collaboration and Team Members](#step-3-collaboration-and-team-members)
		- [Step 4: Development](#step-4-development)
			- [Issues:](#issues)
			- [Branches](#branches)
			- [Commits](#commits)
				- [Guidelines for good commit messages](#guidelines-for-good-commit-messages)
			- [Pull Requests](#pull-requests)
	- [Markdown and README](#markdown-and-readme)
	- [Additional Resources and Documentation:](#additional-resources-and-documentation)
		- [General Documentation](#general-documentation)
		- [Additional Specific Documentation](#additional-specific-documentation)
			- [Quickstart](#quickstart)
			- [Repositories](#repositories)
			- [Branches](#branches-1)
			- [Issues](#issues-1)
			- [Bonus Documentation](#bonus-documentation)

---

## Getting Started

### Shifting Our Design ###
Following our proposal from Project 3a, our group made key design changes. After unanimously determining hash maps would better support our search functionality, we adopted a triple‑nested map approach (City → Star Rating → Price Level) and decided to compare separate chaining vs. open addressing. This made our end goal more feasible as user inputs would now serve as successive keys through these layers until the final list of matching restaurants. To fit this change, we reassigned roles: Anthony built the open addressing hash map, and Elizabeth implemented the separate chaining map.

### Preparing To Code ###
When preparing to code our project, we initialized our GitHub workflow by creating the repo, cloning locally, and becoming comfortable with terminal Git commands. By facilitating an understanding of Git and establishing clear communication, we were able to ensure smooth collaboration amongst all members for the duration of the project. Lastly, with the GitHub foundation set, each member created the files they would work on and researched their assigned module and how to implement it. 

### Prerequisites

- C++17‑compatible compiler (e.g. `g++`, `clang++`)  
- CMake ≥ 3.10 (optional but recommended)  
- Git

### Clone the repo

```bash
git clone https://github.com/<your‑org>/MichelinMunch.git
cd MichelinMunch
