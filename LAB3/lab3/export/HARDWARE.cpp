#include "systemc.h"
#include "../../MAC_proxy.h"
#include "../Monitor.h"
#include "../Pattern.h"
#include "../clockreset.h"
#include "cassert"
#include "cwr_dynamic_loader.h"
#include "cwr_sc_dynamic_stubs.h"
#include "cwr_sc_hierarch_module.h"
#include "cwr_sc_object_creator.h"
#include "scmlinc/scml_abstraction_level_switch.h"
#include "scmlinc/scml_property_registry.h"

using namespace conf;
using namespace std;


class Clock0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    int division = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "division");

    int cycle = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "cycle");

    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Clock/Clock: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Clock::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Clock/Clock: " << hierach_name << " created." << std::endl; }
      Clock* result = new Clock(name.c_str(), division, cycle);
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
      return result;
    }
  }
};

template <class BC>
class BusCreator : public ScObjectCreatorBase
{
  sc_object* create (const string& name) {
    ScGeneratedBaseBlockCreatorHelper helper(getHierarchicalName(name));
    if (helper.is_runtime_disabled()) {
      return new conf::StubBusCreator(name.c_str(), helper);
    } else {
      return new BC(name.c_str(), helper);
    }
  }
};

template <class GBC>
class GeneratedBlockCreator : public ScObjectCreatorBase
{
  sc_object* create (const string& name) {
    ScGeneratedBaseBlockCreatorHelper helper(getHierarchicalName(name));
    if (helper.is_runtime_disabled()) {
      return new conf::StubBusCreator(name.c_str(), helper);
    } else {
      return new GBC(name.c_str(), helper);
    }
  }
};



class MAC0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    string hdlSrcPath = scml_property_registry::inst().getStringProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "hdlSrcPath");

    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "MAC/MAC: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&MAC::clock, "clock" , string(static_cast<sc_object*>(result)->name()) + ".clock" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::reset, "reset" , string(static_cast<sc_object*>(result)->name()) + ".reset" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::a, "a" , string(static_cast<sc_object*>(result)->name()) + ".a" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::b, "b" , string(static_cast<sc_object*>(result)->name()) + ".b" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::c, "c" , string(static_cast<sc_object*>(result)->name()) + ".c" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::a_out, "a_out" , string(static_cast<sc_object*>(result)->name()) + ".a_out" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::b_out, "b_out" , string(static_cast<sc_object*>(result)->name()) + ".b_out" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::c_out, "c_out" , string(static_cast<sc_object*>(result)->name()) + ".c_out" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::result, "result" , string(static_cast<sc_object*>(result)->name()) + ".result" );
       conf::stub_port_registrator<>::register_stub_port(&MAC::done, "done" , string(static_cast<sc_object*>(result)->name()) + ".done" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "MAC/MAC: " << hierach_name << " created." << std::endl; }
      MAC* result = new MAC(name.c_str(), hdlSrcPath.c_str());
       cwr_sc_object_registry::inst().addPort(&result->clock, string(static_cast<sc_object*>(result)->name()) + ".clock" );
       cwr_sc_object_registry::inst().addPort(&result->reset, string(static_cast<sc_object*>(result)->name()) + ".reset" );
       cwr_sc_object_registry::inst().addPort(&result->a, string(static_cast<sc_object*>(result)->name()) + ".a" );
       cwr_sc_object_registry::inst().addPort(&result->b, string(static_cast<sc_object*>(result)->name()) + ".b" );
       cwr_sc_object_registry::inst().addPort(&result->c, string(static_cast<sc_object*>(result)->name()) + ".c" );
       cwr_sc_object_registry::inst().addPort(&result->a_out, string(static_cast<sc_object*>(result)->name()) + ".a_out" );
       cwr_sc_object_registry::inst().addPort(&result->b_out, string(static_cast<sc_object*>(result)->name()) + ".b_out" );
       cwr_sc_object_registry::inst().addPort(&result->c_out, string(static_cast<sc_object*>(result)->name()) + ".c_out" );
       cwr_sc_object_registry::inst().addPort(&result->result, string(static_cast<sc_object*>(result)->name()) + ".result" );
       cwr_sc_object_registry::inst().addPort(&result->done, string(static_cast<sc_object*>(result)->name()) + ".done" );
      return result;
    }
  }
};


class Monitor0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Monitor/Monitor: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Monitor::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::clock, "clock" , string(static_cast<sc_object*>(result)->name()) + ".clock" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::A, "A" , string(static_cast<sc_object*>(result)->name()) + ".A" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::B, "B" , string(static_cast<sc_object*>(result)->name()) + ".B" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::C, "C" , string(static_cast<sc_object*>(result)->name()) + ".C" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::Y, "Y" , string(static_cast<sc_object*>(result)->name()) + ".Y" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::done, "done" , string(static_cast<sc_object*>(result)->name()) + ".done" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Monitor/Monitor: " << hierach_name << " created." << std::endl; }
      Monitor* result = new Monitor(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->clock, string(static_cast<sc_object*>(result)->name()) + ".clock" );
       cwr_sc_object_registry::inst().addPort(&result->A, string(static_cast<sc_object*>(result)->name()) + ".A" );
       cwr_sc_object_registry::inst().addPort(&result->B, string(static_cast<sc_object*>(result)->name()) + ".B" );
       cwr_sc_object_registry::inst().addPort(&result->C, string(static_cast<sc_object*>(result)->name()) + ".C" );
       cwr_sc_object_registry::inst().addPort(&result->Y, string(static_cast<sc_object*>(result)->name()) + ".Y" );
       cwr_sc_object_registry::inst().addPort(&result->done, string(static_cast<sc_object*>(result)->name()) + ".done" );
      return result;
    }
  }
};


class Pattern0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Pattern/Pattern: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Pattern::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&Pattern::clock, "clock" , string(static_cast<sc_object*>(result)->name()) + ".clock" );
       conf::stub_port_registrator<>::register_stub_port(&Pattern::A, "A" , string(static_cast<sc_object*>(result)->name()) + ".A" );
       conf::stub_port_registrator<>::register_stub_port(&Pattern::B, "B" , string(static_cast<sc_object*>(result)->name()) + ".B" );
       conf::stub_port_registrator<>::register_stub_port(&Pattern::C, "C" , string(static_cast<sc_object*>(result)->name()) + ".C" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Pattern/Pattern: " << hierach_name << " created." << std::endl; }
      Pattern* result = new Pattern(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->clock, string(static_cast<sc_object*>(result)->name()) + ".clock" );
       cwr_sc_object_registry::inst().addPort(&result->A, string(static_cast<sc_object*>(result)->name()) + ".A" );
       cwr_sc_object_registry::inst().addPort(&result->B, string(static_cast<sc_object*>(result)->name()) + ".B" );
       cwr_sc_object_registry::inst().addPort(&result->C, string(static_cast<sc_object*>(result)->name()) + ".C" );
      return result;
    }
  }
};


class Reset0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    int _ticks = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "_ticks");

    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Reset/Reset: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Reset::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Reset/Reset: " << hierach_name << " created." << std::endl; }
      Reset* result = new Reset(name.c_str(), _ticks);
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
      return result;
    }
  }
};



extern void scv_tr_cwrdb_init();

int sc_main(int argc, char* argv[])
{
  scv_tr_cwrdb_init();
  ScObjectFactory::inst().addCreator ("Clock0", new Clock0Creator());
  ScObjectFactory::inst().addCreator ("MAC0", new MAC0Creator());
  ScObjectFactory::inst().addCreator ("Monitor0", new Monitor0Creator());
  ScObjectFactory::inst().addCreator ("Pattern0", new Pattern0Creator());
  ScObjectFactory::inst().addCreator ("Reset0", new Reset0Creator());
  ScObjectFactory::inst().addCreator ("sc_signal<bool>", new ScPrimChannelCreator<sc_signal<bool> >());
  ScObjectFactory::inst().addCreator ("sc_signal<sc_uint<4> >", new ScPrimChannelCreator<sc_signal<sc_uint<4> > >());
  ScObjectFactory::inst().addCreator ("sc_signal<sc_uint<8> >", new ScPrimChannelCreator<sc_signal<sc_uint<8> > >());
  ScObjectFactory::inst().addCreator ("sc_signal<sc_uint<9> >", new ScPrimChannelCreator<sc_signal<sc_uint<9> > >());
  ScPortFactory::inst().addCreator ("sc_in<bool>", new ScPortCreator<sc_in<bool> >());
  ScPortFactory::inst().addCreator ("sc_in<sc_uint<4> >", new ScPortCreator<sc_in<sc_uint<4> > >());
  ScPortFactory::inst().addCreator ("sc_in<sc_uint<8> >", new ScPortCreator<sc_in<sc_uint<8> > >());
  ScPortFactory::inst().addCreator ("sc_in<sc_uint<9> >", new ScPortCreator<sc_in<sc_uint<9> > >());
  ScPortFactory::inst().addCreator ("sc_inout<bool>", new ScPortCreator<sc_inout<bool> >());
  ScPortFactory::inst().addCreator ("sc_inout<sc_uint<4> >", new ScPortCreator<sc_inout<sc_uint<4> > >());
  ScPortFactory::inst().addCreator ("sc_inout<sc_uint<8> >", new ScPortCreator<sc_inout<sc_uint<8> > >());
  ScPortFactory::inst().addCreator ("sc_inout<sc_uint<9> >", new ScPortCreator<sc_inout<sc_uint<9> > >());
  ScPortFactory::inst().addCreator ("sc_out<bool>", new ScPortCreator<sc_out<bool> >());
  ScPortFactory::inst().addCreator ("sc_out<sc_uint<4> >", new ScPortCreator<sc_out<sc_uint<4> > >());
  ScPortFactory::inst().addCreator ("sc_out<sc_uint<8> >", new ScPortCreator<sc_out<sc_uint<8> > >());
  ScPortFactory::inst().addCreator ("sc_out<sc_uint<9> >", new ScPortCreator<sc_out<sc_uint<9> > >());
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Clock/Clock loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "MAC/MAC loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Monitor/Monitor loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Pattern/Pattern loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Reset/Reset loaded." << std::endl; }

  scml_property_registry::inst().setXMLFile("Properties.xml");

  nSnps::nDynamicLoading::DynamicLoader dynamicLoader
    (scml_property_registry::inst().getStringProperty(scml_property_registry::GLOBAL, "", "/pct/runtime/dynamic_load_info"));

  string xml_file_path = scml_property_registry::inst().getPropertyXmlFilePath();
  string hierarchy_xml_file = xml_file_path + "/" + 
    scml_property_registry::inst().getStringProperty(
      scml_property_registry::GLOBAL, "", "system_hierarchy_xml_file");

  unique_ptr<cwr_sc_hierarch_module> HARDWARE ( new cwr_sc_hierarch_module("HARDWARE", hierarchy_xml_file));

  // Enable/disable backdoor accesses
  scml_abstraction_level_switch::instance().set_simulation_mode(scml_property_registry::inst().getStringProperty(scml_property_registry::GLOBAL, "", "/pct/runtime/simulation_mode")=="MODE_FULL_SIMULATION" ? scml_abstraction_level_switch::MODE_FULL_SIMULATION : scml_abstraction_level_switch::MODE_SPEED_OPTIMIZED);

  try {
    sc_start();
  } catch (const sc_core::sc_report& sce) { 
    std::cout << "Exception raised by sc_start() : " << sce.what() << std::endl;  
    return 1;  
  } 

  if (sc_is_running()) {
    sc_stop();
  }

  return 0;
}
