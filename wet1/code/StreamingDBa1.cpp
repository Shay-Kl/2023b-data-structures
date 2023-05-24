#include "StreamingDBa1.h"
#include <new>
#include "wet1util.h"
#include <memory>

streaming_database::streaming_database():
	movies(), users(), groups(), genreMovies()
	{}

streaming_database::~streaming_database()
{
	//Every tree's destructor does the job
}


void streaming_database::getAllAux(AVLtree<Movie, int>::Node* root, int* output, int& index)
{
	if (!root){
        return;
    }
	getAllAux(root->getLeft(), output, index);
	Movie& temp = root->key;
	output[index] = temp.getId();
	index++;
	getAllAux(root->getRight(), output, index);
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

		//Allocate all of the memory before starting to change the trees to prevent changes in case of bad alloc
		unique_ptr<AVLtree<int, Movie>::Node> movieNode1(new AVLtree<int, Movie>::Node(movieId, movie));
		unique_ptr<AVLtree<Movie, int>::Node> movieNode2(new AVLtree<Movie,int>::Node(movie, 0));
		unique_ptr<AVLtree<Movie, int>::Node> movieNode3(new AVLtree<Movie,int>::Node(movie, 0));

		movies.insertNode(movieNode1.release());
		genreMovies[(int)genre].insertNode(movieNode2.release());
		genreMovies[(int)Genre::NONE].insertNode(movieNode3.release());
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
		User* user = &users.get(userId);
		if (user->getGroup())
		{
			shared_ptr<Group> group = user->getGroup();
			group->removeUser(user);
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
		groups.insert(groupId, shared_ptr<Group>(new Group(groupId)));
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
		shared_ptr<Group> group = groups.get(groupId);
		group->closeGroup();
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
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	if (groupId <= 0 || userId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	try
	{
		User* user = &users.get(userId);
		shared_ptr<Group> group = groups.get(groupId);
		group->addUser(user);
		user->addToGroup(group, groupId);
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

		Movie updatedMovie(movie);
		updatedMovie.view();

		unique_ptr<AVLtree<Movie, int>::Node> movieNode1(new AVLtree<Movie,int>::Node(updatedMovie, 0));
		unique_ptr<AVLtree<Movie, int>::Node> movieNode2(new AVLtree<Movie,int>::Node(updatedMovie, 0));

		user.watch(genre);

		genreMovies[(int)genre].remove(movie);
		genreMovies[(int)Genre::NONE].remove(movie);

		movie.view();
		genreMovies[(int)Genre::NONE].insertNode(movieNode1.release());
		genreMovies[(int)genre].insertNode(movieNode2.release());
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
		shared_ptr<Group> group = groups.get(groupId);
		int members_in_group = group->getUsersCount();
		if (members_in_group == 0 || (movie.isVipOnly() && !group->isVip()))
		{
			return StatusType::FAILURE;
		}

		Movie updatedMovie(movie);
		updatedMovie.view(members_in_group);

		unique_ptr<AVLtree<Movie, int>::Node> movieNode1(new AVLtree<Movie,int>::Node(updatedMovie, 0));
		unique_ptr<AVLtree<Movie, int>::Node> movieNode2(new AVLtree<Movie,int>::Node(updatedMovie, 0));

		group->groupWatch(genre);

		genreMovies[(int)genre].remove(movie);
		genreMovies[(int)Genre::NONE].remove(movie);

		movie.view(members_in_group);
		genreMovies[(int)Genre::NONE].insertNode(movieNode1.release());
		genreMovies[(int)genre].insertNode(movieNode2.release());

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
		if (genreMovies[(int)genre].getNodeCount() == 0)
		{
			return StatusType::FAILURE;
		}
		int index = 0;
		getAllAux(genreMovies[(int)genre].getRoot(), output, index);

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

		Movie updatedMovie(movie);
		updatedMovie.rate(rating);

		unique_ptr<AVLtree<Movie, int>::Node> movieNode1(new AVLtree<Movie,int>::Node(Movie(updatedMovie), 0));
		unique_ptr<AVLtree<Movie, int>::Node> movieNode2(new AVLtree<Movie,int>::Node(Movie(updatedMovie), 0));


		genreMovies[(int)genre].remove(movie);
		genreMovies[(int)Genre::NONE].remove(movie);

		movie.rate(rating);
		genreMovies[(int)Genre::NONE].insertNode(movieNode1.release());
		genreMovies[(int)genre].insertNode(movieNode2.release());

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
		shared_ptr<Group> group = groups.get(groupId);
		if (group->getUsersCount() == 0)
		{
			return StatusType::FAILURE;
		}
		Genre favorit_genre = Genre::COMEDY;
		int favorit_genre_views = 0;
		for (int i = 0; i < 4; i++)
		{
			int temp = group->getGenreViewCount((Genre)i);
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
		int favorit_movie_id = (genreMovies[(int)favorit_genre].getMin()->key).getId();
		
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