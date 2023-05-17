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
		User user(userId, isVip);
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
		User& user = users.get(userId);
		Group* group_ptr = user.getGroup();
		if (group_ptr)
		{
			group_ptr->removeUser(user);
		}
		users.remove(userId);
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
	if(groupId <= 0 )
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		Group group(groupId);
		groups.insert(groupId, group);
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

StatusType streaming_database::remove_group(int groupId)
{
	if (groupId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		Group& group = groups.get(groupId);
		AVLtree<int, User*> group_users = group.getUsers();
		for (AVLtree<int, User*>::Iterator it = group_users.begin();
			it != group_users.end(); ++it)
		{
			User& user = *(it.value());
			group.removeUser(user);
			user.removeFromGroup();
		}
		groups.remove(groupId);
		
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
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	if (groupId <= 0 || userId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		User& user = users.get(userId);
		Group& group = groups.get(groupId);
		group.addUser(user);
		user.addToGroup(&group, groupId);
	}
	catch(bad_alloc)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(exception)
	{
		return StatusType::FAILURE;
	}
	
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
		user.watch(genre);

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
	if (groupId <= 0 || movieId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		Movie& movie = movies.get(movieId);
		Genre genre = movie.getGenre();
		Group& group = groups.get(groupId);
		int members_in_group = group.getUsersCount();
		if (members_in_group == 0 || (movie.isVipOnly() && !group.isVip()))
		{
			return StatusType::FAILURE;
		}
		else
		{
			genreMovies[(int)genre].remove(movie);
			genreMovies[(int)Genre::NONE].remove(movie);
			movie.view(members_in_group);
			genreMovies[(int)genre].insert(movie, 0);
			genreMovies[(int)Genre::NONE].insert(movie, 0);

			group.updateViews(genre, members_in_group);
			group.incGroupWatch(genre);

			return StatusType::SUCCESS;
		}
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
		return user.getEffectiveViews(genre);
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
	try
	{
		if (groupId <= 0)
		{
			return StatusType::INVALID_INPUT;
		}
		Group& group = groups.get(groupId);
		if (group.getUsersCount() == 0)
		{
			return StatusType::FAILURE;
		}
		Genre favorit_genre = Genre::COMEDY;
		int favorit_genre_views = 0;
		for (int i = 0; i < 4; i++)
		{
			int temp = group.getGenreViewCount((Genre)i);
			if(temp > favorit_genre_views)
			{
				favorit_genre = (Genre)i;
				favorit_genre_views = temp;
			}
		}
		if (genreMovies[(int)favorit_genre].getNodeCount() == 0)
		{
			return StatusType::FAILURE;
		}
		int favorit_movie_id = (*(genreMovies[(int)favorit_genre].begin())).getId();
		
		return favorit_movie_id;
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


