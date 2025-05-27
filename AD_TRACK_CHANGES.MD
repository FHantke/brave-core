# Enabling Ad Tracking in Brave
This guide outlines the necessary changes to enable tracking for subresource filtering usable in WebAPIs and to ensure your own rulesets are properly indexed and published within Brave.

## 1. Enaable Trackingg in `common_features.cc`
We edited the following file to enable `kAdTagging`
```
chromium_src/components/subresource_filter/core/common/common_features.cc
```

## 2. Enable Runtime Feature
Tracking must also be enabled in the runtime feaatures in the following file (not part of this repo).
```
src/third_party/blink/renderer/platform/runtime_enabled_features.json5
```

Change the AdTagging entry to stable as shown below:
```json
{
    name: "AdTagging",
    public: true,
    status: "stable"
}
```

## 3. Update `ruleset_service.cc` for Filterlist Management
The filw to modify:
```
chromium_src/components/subresource_filter/content/shared/browser/ruleset_service.cc
```

First, make sure the constructor of the ruleset service calls opens and publishes our ruleset. In the constructor of `RulesetService::RulesetService`, ccomment out the validaation check and add `OpenAndPublishRuleset(most_recently_indexed_version);` afterwards. You can now add your own indexed filterlist as rulseset `0` to the Subresource Filter directory (see end of this readme).

Second, update the current format directory cconsidered during the `DeleteObsoleteRulesets` funcction by adding this line after the original `current_format_dir` setup. This ensures our added filterlist is not deleted after eaacch run.
```c++
base::FilePath current_format_dir(indexed_ruleset_base_dir.AppendASCII("0"));

```

## 4. Add Ad Check to API Calls
Once the above steps are completed, youu can get information about the tracking/ad context in any API call with referig to the execution context. For example in the `BatteryManager`:

```c++
/* src/brave/chromium_src/third_party/blink/renderer/modules/battery/battery_manager.cc
*/

ScriptPromise<BatteryManager> BatteryManager::StartRequest(
		ScriptState* script_state) {
	ExecutionContext* context = ExecutionContext::From(script_state);
	AdTracker* tracker = AdTracker::FromExecutionContext(context);
	bool is_ad = tracker && tracker-> IsAdScriptInStack(
		AdTracker::StackType::kBottomAndTop);

	LOG(ERROR) << "[Battery API] Called from ad? " << (is_ad ? "YES" : "NO");
```

# Add Modified Filterlist
First, you need to build the subresource filter tools for chromium:
```bash
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
export PATH="/Users/fhantke/Documents/Tools/chrome/depot_tools:$PATH"
mkdir chromium && cd chromium  
fetch --nohooks --no-history chromium
cd src
gclient sync
gn gen out/Default
autoninja -C out/Default subresource_filter_tools
```

Then, you can index your filter list.
```bash
path/to/chromium/src/out/Default/ruleset_converter --input_format=filter-list --output_format=unindexed-ruleset --input_files=./simple_list.txt --output_file=simplelist_unindexed
path/to/chromium/src/out/Default/subresource_indexing_tool simplelist_unindexed simplelist_indexed
```

Add this filter list to your Brave, for example in `~/Library/Application Support/BraveSoftware/Brave-Browser-Development`:
```bash
mkdir -p Subresource\ Filter/Indexed\ Rules/0
cp path/to/filterlists/simplelist_indexed Subresource\ Filter/Indexed\ Rules/0/Ruleset\ Data
```

