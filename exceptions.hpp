#pragma once

#include <stdexcept>
#include <string>

/// Car crossed moved into its nearest barrier space and its speed is not 0.
class Car_crossed_barrier : public std::logic_error
{
public:
	explicit Car_crossed_barrier(std::string const& message);
	Car_crossed_barrier(char const* exception);

	virtual const char* what() const throw() override;

private:
	std::string message;
};

/// Car is in Car_degenerator, but its  where_to_go method says that it is not its final destination.
class Car_is_not_to_be_deleted : public std::logic_error
{
public:
	explicit Car_is_not_to_be_deleted(std::string const& message);
	Car_is_not_to_be_deleted(char const* exception);

	virtual const char* what() const throw() override;

private:
	std::string message;
};

/// Car path is of 0 size whereas its always shall be positive. Final desination is marked as nullptr.
class Car_path_size_is_not_positive : public std::logic_error
{
public:
	explicit Car_path_size_is_not_positive(std::string const& message);
	Car_path_size_is_not_positive(char const* exception);

	virtual const char* what() const throw() override;

private:
	std::string message;
};

/// Model object is calles a method that requirs it to be built. Yet it hasn't been built.
class Model_object_is_not_built : public std::logic_error
{
public:
	explicit Model_object_is_not_built(std::string const& message);
	Model_object_is_not_built(char const* exception);

	virtual const char* what() const throw() override;

private:
	std::string message;
};

/// Some method calles out_of_range value. Used to get where seg_fault occured.
class Model_object_segmentation_fault : public std::logic_error
{
public:
	explicit Model_object_segmentation_fault(std::string const& message);
	Model_object_segmentation_fault(char const* exception);

	virtual const char* what() const throw() override;

private:
	std::string message;
};

/// Attempt to build a model second time. It is not permitted.
class Model_object_repeated_build : public std::logic_error
{
public:
	explicit Model_object_repeated_build(std::string const& message);
	Model_object_repeated_build(char const* exception);

	virtual const char* what() const throw() override;

private:
	std::string message;
};

/// Unexpected argument in building Cross_road.
class Cross_road_unexpected_argument : public std::logic_error
{
public:
	explicit Cross_road_unexpected_argument(std::string const& message);
	Cross_road_unexpected_argument(char const* exception);

	virtual const char* what() const throw() override;

private:
	std::string message;
};

