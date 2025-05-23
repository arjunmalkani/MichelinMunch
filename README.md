  # MichelinMunch
  **UF COP3530 Project 3 by Anthony Perez, Arjun Malkani, and Elizabeth Gonzalez**

A C++ CLI based program for discovering affordable Michelin‑rated restaurants using two custom hash‑map implementations (separate‑chaining & open‑addressing) and timing their performance to see which has better results.

## Features

- **Triple‑layered maps** by City → Star Rating → Price Level   
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
   - [Shifting Our Design](#shifting-our-design)
   - [Preparing To Code](#preparing-to-code)
		
- [Usage](#usage)
- [Plagiarism Notice](#plagiarism-notice)
---

## Getting Started

### Shifting Our Design ###
Following our proposal from Project 3a, our group made key design changes. After unanimously determining hashmaps would better support our search functionality, we adopted a triple‑nested map approach (City → Star Rating → Price Level) and decided to compare separate chaining vs. open addressing. This made our end goal more feasible as user inputs would now serve as successive keys through these layers until the final list of matching restaurants. To fit this change, we reassigned roles: Anthony built the open addressing hashmap, and Elizabeth implemented the separate chaining map.

### Preparing To Code ###
When preparing to code our project, we initialized our GitHub workflow by creating the repo, cloning locally, and becoming comfortable with terminal Git commands. By facilitating an understanding of Git and establishing clear communication, we were able to ensure smooth collaboration amongst all members for the duration of the project. Lastly, with the GitHub foundation set, each member created the files they would work on and researched their assigned module and how to implement it. 

## Usage
### Running the Program ##
To run our program, first clone the repository. Once cloned, open the project in CLion and navigate to the cloned folder.  CLion will automatically detect and load the CMake project. After the project finishes indexing and building, you can run the program by clicking the green "Run" button in the top-right corner or pressing Shift + F10. The program will execute from the default main executable.

## Plagiarism Notice
This project belongs to Anthony Perez, Elizabeth Gonzalez, and Arjun Malkani **ONLY**. If there is any form of plagiarism or use of our work without proper credit, we will not be afraid take action in order to defend our self image and personal integrity. 
