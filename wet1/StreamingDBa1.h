// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "Movie.h"
#include "User.h"
#include "Group.h"
#include "AVL_tree.h"

class User;
class Group;

class streaming_database {
private:
	AVLtree<int, Movie> movies;
	AVLtree<int, shared_ptr<User>> users;
	AVLtree<int, shared_ptr<Group>> groups;
	AVLtree<int, AVLtree<int, shared_ptr<User>>> groupUsers;
	AVLtree<Movie, int> genreMovies[5];

	template <class Key ,class Value>
	void removeUserAux(Node<Key, Value>* root, shared_ptr<Group>& group);
	
	template <class Key ,class Value>
	void getAllAux(Node<Key, Value>* root, int* output);

public:
	// <DO-NOT-MODIFY> {
	
	streaming_database();

	virtual ~streaming_database();
	
	StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);
	
	StatusType remove_movie(int movieId);
	
	StatusType add_user(int userId, bool isVip);
	
	StatusType remove_user(int userId);
	
	StatusType add_group(int groupId);
	
	StatusType remove_group(int groupId);

	StatusType add_user_to_group(int userId, int groupId);
	
	StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);
	
	output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);
	
	output_t<int> get_group_recommendation(int groupId);
	
	// } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
