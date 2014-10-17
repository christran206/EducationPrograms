--------------------------------------------------------------------------------
1. All classes are working as expected so far. After a fair amount of
unit and integration testing before I combined more objects, I had
expected behaviour.

2. PatronDB is using a STL hash map to allow a dynamically increasing 
container that can be changed to a different key mapping

LibActionFactory is also using an STL Hash map to store the LibAction
class objects using the character as the key

Shelf class itself is my hash implementation. The char type is used 
to store to an index. Any publication being inserted will automatically
go into the proper location in the vector that holds BSTree objects without
the need for any external knowledge of the function of the Shelf Class.

3. Patron data is read in the PatronDB class with the build function
and is inserted into the map using the int ID as the key pair. This results
in the patrons being stored in sorted order by ID, but this can be easily changed

Book data is read in the Shelf class in the buildShelf function
using the character as the key to the location of a BSTreee where data is 
inserted in sorted order

4. Command data is read in the Librarian class in the build function. Each line
is processed as soon as it's read instead of storing all the commands
in a container before processing.

5. The reading of the text files ended up using switch statements.
Other methods were overly complicated and didn't make sense. Originally
I had another factory class that could build each book from the file
but handling non valid books became a significant challenge where the
obvious solution was to create an enum with valid book chars and check
the enum.

I opted to change it to an entirely contained function since the
function itself is specific to the file. The class itself still
allows other insertion methods such as text input so it can still
be extended to support other options.

I bent the rules but I don't believe I completely broke them since
a change in the function doesn't require changes to the other
classes.

6. I built three programs from the ground up.
The first and third attempts at my program had no memory leaks.
Using the experience of unit testing and integration testing
that I'm learning at work, I was able to compile, run, and have
no leaks.

My second program was an entire attempt to design with an abundance
of objects like Ruby development. I ended up with 39 classes each with 
a specific purpose.

I had a factory that could produce builder objects that would take in
the lines of data and return the object. However, this only worked
for the valid book children as the invalid children were producing errors
that I didn't feel I had the time to solve this bug.