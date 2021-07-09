#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "genetic_algorithm.hpp"
#include "io.h"

// Parameters to control the evolution
unsigned max_iterations = 3000;
double fitness_target = 1.0;
double fitness_best = 0;
unsigned number_elites = 2;
double probability_crossover = 0.9;
double probability_mutation = 0.8;

// Population parameters
unsigned size_population = 500;
unsigned size_genome = 60;
int gene_bound_upper = 1;
int gene_bound_lower = 0;

// Dataset parameters
double split = 0.7;

// Storing generations and best individuums
std::vector<genome> population_parents;
std::vector<genome> population_children;
std::vector<genome> best_individuums;

int main(){

    std::vector<std::vector<double>> mines = read_csv("./data/mines.csv");
    std::vector<std::vector<double>> rocks = read_csv("./data/rocks.csv");
    std::vector<std::vector<double>> training_data;
    std::vector<std::vector<double>> testing_data;
    unsigned number_mines_training = split*mines.size();
    unsigned number_rocks_training = split*mines.size();
    unsigned number_mines_testing = mines.size() - number_mines_training;
    unsigned number_rocks_testing = rocks.size() - number_rocks_training;
    training_data.reserve(number_mines_training + number_rocks_training);
    testing_data.reserve(number_mines_testing + number_rocks_testing);
    for(unsigned i = 0; i < number_mines_training; i++){
        training_data.push_back(mines[i]);
    }
    for(unsigned i = 0; i < number_rocks_training; i++){
        training_data.push_back(rocks[i]);
    }
    for(unsigned i = number_mines_training; i < mines.size(); i++){
        testing_data.push_back(mines[i]);
    }
    for(unsigned i = number_rocks_training; i < rocks.size(); i++){
        testing_data.push_back(rocks[i]);
    }

    // Initialize/prepare populations
    population_parents = generate_random_population(size_population, size_genome, gene_bound_lower, gene_bound_upper);
    population_children.reserve(size_population);

    // Evolve new generations
    // loop is left when a maximum of iterations is reached
    // or a desired fitness has been reached
    for(int i = 0; i < max_iterations && fitness_target > fitness_best; i++){
        
        // Evaluate the fitness of each population member
        evaluate_population(population_parents, training_data);

        // Sort the population by the fitness of the members
        sort_population(population_parents);

        // Save the best individuum and its fitness
        // if an improvement has been made
        if (population_parents[0].fitness > fitness_best){
            fitness_best = population_parents[0].fitness;
            best_individuums.push_back(population_parents[0]);
        }

        // Copy the n best individuums into the child generation
        use_elitism(population_children, population_parents, number_elites);
        
        // use the parent generation to fill up the rest of the
        // child generation with modified versions
        crossover(population_children, population_parents, probability_crossover, size_population - number_elites);
        mutate_population(population_children, probability_mutation, number_elites, gene_bound_lower, gene_bound_upper);

        // Set the children population as the new parent population
        // clear the population_children to prevent growing populations
        population_parents = population_children;
        population_children.clear();
        
    }

    printf("----------------------\n");
    printf("Population of best individuums:\n");
    printf("----------------------\n");
    for(auto& individuum : best_individuums){
        printf("Accuracy Training: %lf\n", calculate_accuracy(individuum, training_data));
        printf("Accuracy Testing: %lf\n", calculate_accuracy(individuum, testing_data));
        printf("----------------------\n");
    }
    return 0;
}