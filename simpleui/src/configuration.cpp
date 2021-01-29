#pragma once

// library headers
#include <configuration.hpp>

/** An implementation of Configuration that simply takes its parameter as a list
 * of values on the command-line.
 */
class Config:
		public Configuration
{
	/// number of iterations to execute
	int m_nb_iter;
	
	/// shape of the global data field
	Coord2D m_global_shape;
	
	/// shape of the data distribution
	Coord2D m_dist_extents;
	
	/// time difference between two consecutive points
	double m_delta_t;
	
	/// space difference between two consecutive points
	std::array<double, 2> m_delta_space;
	
public:
	/** Construct a new CommandLineConfig
	 * @param argc the number of command-line arguments
	 * @param argv the values of command-line arguments
	 */
	Config(const int nb_iter, const char* param);
	
	// see overridden function
	int nb_iter() const override { return m_nb_iter; }
	
	// see overridden function
	Coord2D global_shape() const override { return m_global_shape; }
	
	// see overridden function
	Coord2D dist_extents() const override { return m_dist_extents; }
	
	// see overridden function
	double delta_t() const override { return m_delta_t; }
	
	// see overridden function
	std::array<double, 2> delta_space() const override { return m_delta_space; }
	
};
