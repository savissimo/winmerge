#ifndef PluginManager_h_included
#define PluginManager_h_included

#define POCO_NO_UNWINDOWS 1
#include <Poco/Mutex.h>
#include <boost/shared_ptr.hpp>
#include <map>
// defines IPluginInfos
#include "DiffContext.h"
// defines PackingInfo and PrediffingInfo
#include "FileTransform.h"

/**
 * @brief Cached plugin info for one particular file info
 */
struct PluginFileInfo
{
	PackingInfo m_infoUnpacker;
	PrediffingInfo m_infoPrediffer;
};

typedef boost::shared_ptr<PluginFileInfo> PluginFileInfoPtr;

/**
 * @brief Cache of known plugin infos
 */
class PluginManager : public IPluginInfos
{
public:
	typedef std::map<String, PluginFileInfoPtr> PluginFileInfoMap;

	~PluginManager();
	void SetPrediffSetting(const String& filteredFilenames, int newsetting);
	void SetPrediffSettingAll(int newsetting);
	void SetPrediffer(const String& filteredFilenames, const String& prediffer);

private:
	// Implement IPluginInfos
	virtual void FetchPluginInfos(const String& filteredFilenames, 
                                      PackingInfo ** infoUnpacker, 
                                      PrediffingInfo ** infoPrediffer);
private:
	// Data
	PluginFileInfoMap m_pluginSettings;
	Poco::FastMutex m_mutex;
};

#endif // PluginManager_h_included