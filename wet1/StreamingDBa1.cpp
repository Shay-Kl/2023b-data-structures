#include "StreamingDBa1.h"
#include <new>
#include "wet1util.h"

streaming_database::streaming_database():
	movies(), users(), groups(), genreMovies()
	{}

streaming_database::~streaming_database()
{
	//Every tree's destructor does the job
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
	if(movieId<=0 || genre==Genre::NONE || views<0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		Movie movie(genre, views, vipOnly, movieId);
		movies.insert(movieId, movie);
		genreMovies[(int)genre].insert(movie, 0);
		genreMovies[(int)Genre::NONE].insert(movie, 0);
		return StatusType::SUCCESS;
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
}

StatusType streaming_database::remove_movie(int movieId)
{
	if(movieId<=0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		Movie& movie = movies.get(movieId);
		Genre genre = movie.getGenre();
		
		genreMovies[(int)genre].remove(movie);
		genreMovies[(int)Genre::NONE].remove(movie);
		movies.remove(movieId);
		return StatusType::SUCCESS;
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
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
		users.insert(userId, user);
		return StatusType::SUCCESS;
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
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
		//TODO: remove user from group maybe?
		return StatusType::SUCCESS;
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
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
	if (userId <= 0 || movieId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		Movie& movie = movies.get(movieId);
		User& user = users.get(userId);
		Genre genre = movie.getGenre();
		if (movie.isVipOnly() && !user.isVip())
		{
			return StatusType::FAILURE;
		}
		
		genreMovies[(int)genre].remove(movie);
		genreMovies[(int)Genre::NONE].remove(movie);
		user.watch(movie.getGenre());
		movie.view();
		genreMovies[(int)Genre::NONE].insert(movie, 0);
		genreMovies[(int)genre].insert(movie, 0);
    	return StatusType::SUCCESS;
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
	try
	{
    	return genreMovies[(int)genre].getNodeCount();
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
	
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
	if(output==NULL)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		int i = 0;
		for (const Movie& movie: genreMovies[(int)genre])
		{
			output[i] = movie.getId();
			i++;
		}
		if (i == 0)
		{
			return StatusType::FAILURE;
		}
		
		return StatusType::SUCCESS;
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	if (userId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	
	try
	{
		User& user = users.get(userId);
		return user.getGenreViewCount(genre);
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if (userId <= 0 || movieId <= 0 || rating < 0 || rating > 100)
	{
		return StatusType::INVALID_INPUT;
	}
	
	try
	{
		User& user = users.get(userId);
		Movie& movie = movies.get(movieId);
		Genre genre = movie.getGenre();
		if (movie.isVipOnly() && !user.isVip())
		{
			return StatusType::FAILURE;
		}

		genreMovies[(int)genre].remove(movie);
		genreMovies[(int)Genre::NONE].remove(movie);
		movie.rate(rating);
		genreMovies[(int)genre].insert(movie, 0);
		genreMovies[(int)Genre::NONE].insert(movie, 0);

		return StatusType::SUCCESS;
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
	return 0;
}


