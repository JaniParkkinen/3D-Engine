#ifndef Resource_H
#define Resource_H
#include <string>

//http://gamedev.stackexchange.com/questions/17066/designing-a-resourcemanager-class/17082#17082
namespace Engine {
	typedef enum class Resource_Type
	{
		Resource_Null = 0,
		Resource_Graphics = 1,
		Resource_Movie = 2,
		Resource_Audio = 3,
		Resource_Text = 4,
	}Resource_Type;

	class Resource //: public EngineObject
	{
	public:
		Resource() : resourceID(0), _scope(0), _type(Resource_Type::Resource_Null) {}
		~Resource() {}
		void Load();
		void Unload();

		void SetResourceID(unsigned ID) { resourceID = ID; }
		unsigned GetResourceID() const { return resourceID; }

		void SetFilename(std::string filename) { _filename = filename; }
		std::string GetFilename() const { return _filename; }

		void SetResourceType(Resource_Type type) { _type = type; }
		Resource_Type GetResourceType() const { return _type; }

		void SetResourceScope(unsigned scope) { _scope = scope; }
		signed GetResourceScope() const { return _scope; }

		bool IsLoaded() const { return _loaded; }
		void SetLoaded(bool value) { _loaded = value; }

	protected:
		signed resourceID;
		signed _scope;
		std::string _filename;
		std::string _filepath;
		Resource_Type _type;
		bool _loaded;
	};
}

#endif // !Resource_H