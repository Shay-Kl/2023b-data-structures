#include "StreamingDBa1.h"
#include <new>
#include "wet1util.h"

streaming_database::streaming_database():
	movies(), users(), groups()
	{}

streaming_database::~streaming_database()
{
	//Every tree's default destructor does the job
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
	if(movieId<=0 || genre==Genre::NONE || views<0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		Movie movie(genre, views, vipOnly);
		movies.insert(movie, movieId);
	}
	catch(const std::bad_alloc& e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(BinaryTree::FailureException)
	{
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
	if(movieId<=0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		movies.remove(movieId);
	}
	catch(const std::bad_alloc& e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(BinaryTree::FailureException)
	{
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	if(userId<=0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		User user(isVip);
		users.insert(user, userId);
	}
	catch(const std::bad_alloc& e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(BinaryTree::FailureException)
	{
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
	if(userId<=0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		users.remove(userId);
	}
	catch(const std::bad_alloc& e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(BinaryTree::FailureException)
	{
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}


