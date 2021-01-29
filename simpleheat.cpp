#include <mpi.h>
#include <iostream>
#include <iterator>

#include "boost/boost/program_options.hpp"
#include "commandlineconfig.hpp"
#include "configuration.hpp"
#include "finitediffheatsolver.hpp"
#include "fixedconditions.hpp"
#include "simulation.hpp"
#include "screenprinter.hpp"

namespace po = boost::program_options
{

namespace std;



int main( int argc, char* argv[] )
{
	// initialize the MPI library
	MPI_Init( &argc, &argv );
	  try
	  {
	    po::option_description desc("Parametres");
	    desc.add_options()
	      ("help,h", "Help screen")
	      ("Nb_iter", po::value<int>()->default_value(10), "Nb_iter")
	      ("height", po::value<int>()->default_value(4), "height")
	      ("width", po::value<int>()->default_value(8), "width")
	      ("process_height", po::value<int>()->default_value(1), "process_height")
	      ("process_width", po::value<int>()->default_value(1), "process_width")
	      ("delta_t", po::value<double>()->default_value(0.125), "delta_t")
	      ("delta_x", po::value<double>()->default_value(1), "delta_x")
	      ("delta_y", po::value<double>()->default_value(1), "delta_y")
	      ("file_name", po::value<char*>()->default_value(NULL), "file_name");

	    po::variables_map vm;
	    po::store(parse_command_line(argc, argv, desc), vm);
	    po::notify(vm);

	    if (vm.count("help"))
	      std::cout << desc << '\n';
	    else if (vm.count("Nb_iter"))
	      std::cout << "Nombre d'iterations: " << vm["Nb_iter"].as<int>() << '\n';
	    else if (vm.count("height"))
	      std::cout << "height: " << vm["height"].as<int>() << '\n';
	  	else if (vm.count("width"))
	      std::cout << "width: " << vm["width"].as<int>() << '\n';
	  	else if (vm.count("process_height"))
	      std::cout << "process height: " << vm["process_height"].as<int>() << '\n';
	  	else if (vm.count("process_width"))
	      std::cout << "process_width: " << vm["process_width"].as<int>() << '\n';
	  	else if (vm.count("delta_t"))
	      std::cout << "delta_t: " << vm["delta_t"].as<double>() << '\n';
	  	else if (vm.count("delta_x"))
	      std::cout << "delta_x: " << vm["delta_x"].as<double>() << '\n';
	  	else if (vm.count("delta_y"))
	      std::cout << "delta_y: " << vm["delta_y"].as<double>() << '\n';
	  	else if (vm.count("file_name"))
	      std::cout << "file_name: " << vm["file_name"].as<char*>() << '\n';
	  }
	  catch (const error &ex)
	  {
	    std::cerr << ex.what() << '\n';
	  }
       
      int N = 8;
      char* param = (char*)malloc(sizeof(char)*N);
      param[0] = vm.count("Nb_iter");
      param[1] = vm.count("height");
      param[2] = vm.count("width");
      param[3] = vm.count("process_height");
      param[4] = vm.count("process_width");
      param[5] = vm.count("delta_t");
      param[6] = vm.count("delta_x");
      param[7] = vm.count("delta_y");
	// Construct the command-line arguments parser
	  Config config(N, param);
	 //CommandLineConfig config( argc, argv );

	// construct the heat equation solver

	FinitediffHeatSolver heat_solver( config );
	// construct the initial condition setter
	FixedConditions init;
	// construct the simulation runner
	Simulation simulation( MPI_COMM_WORLD, config, heat_solver, init );
	// Add a printer to screen to observe the simulation
	ScreenPrinter printer;
	simulation.observe( printer );

	// run the simulation
	simulation.run();

	// finalize MPI
	MPI_Finalize();

	return 0;
}
}//po