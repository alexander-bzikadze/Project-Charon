#include "exceptions.hpp"

using std::string;
using std::logic_error;

Car_crossed_barrier::Car_crossed_barrier(string const& message) : 
	logic_error(message) ,
	message(message)
	{}

Car_crossed_barrier::Car_crossed_barrier(char const* message): 
	logic_error(message) ,
	message(message)
	{}

const char* Car_crossed_barrier::what() const throw()
{
	return message.c_str();
}

Car_is_not_to_be_deleted::Car_is_not_to_be_deleted(string const& message) : 
	logic_error(message) ,
	message(message)
	{}

Car_is_not_to_be_deleted::Car_is_not_to_be_deleted(char const* message): 
	logic_error(message) ,
	message(message)
	{}

const char* Car_is_not_to_be_deleted::what() const throw()
{
	return message.c_str();
}

Car_path_size_is_not_positive::Car_path_size_is_not_positive(string const& message) : 
	logic_error(message) ,
	message(message)
	{}

Car_path_size_is_not_positive::Car_path_size_is_not_positive(char const* message): 
	logic_error(message) ,
	message(message)
	{}

const char* Car_path_size_is_not_positive::what() const throw()
{
	return message.c_str();
}

Model_object_is_not_built::Model_object_is_not_built(string const& message) : 
	logic_error(message) ,
	message(message)
	{}

Model_object_is_not_built::Model_object_is_not_built(char const* message): 
	logic_error(message) ,
	message(message)
	{}

const char* Model_object_is_not_built::what() const throw()
{
	return message.c_str();
}

Model_object_segmentation_fault::Model_object_segmentation_fault(string const& message) : 
	logic_error(message) ,
	message(message)
	{}

Model_object_segmentation_fault::Model_object_segmentation_fault(char const* message): 
	logic_error(message) ,
	message(message)
	{}

const char* Model_object_segmentation_fault::what() const throw()
{
	return message.c_str();
}

Model_object_repeated_build::Model_object_repeated_build(string const& message) : 
	logic_error(message) ,
	message(message)
	{}

Model_object_repeated_build::Model_object_repeated_build(char const* message): 
	logic_error(message) ,
	message(message)
	{}

const char* Model_object_repeated_build::what() const throw()
{
	return message.c_str();
}

Cross_road_unexpected_argument::Cross_road_unexpected_argument(string const& message) : 
	logic_error(message) ,
	message(message)
	{}

Cross_road_unexpected_argument::Cross_road_unexpected_argument(char const* message): 
	logic_error(message) ,
	message(message)
	{}

const char* Cross_road_unexpected_argument::what() const throw()
{
	return message.c_str();
}