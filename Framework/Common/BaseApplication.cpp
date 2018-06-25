#include "BaseApplication.hpp"

bool My::BaseApplication::m_bQuit = false;
My::BaseApplication::BaseApplication(GfxConfiguration& cfg) :m_Config(cfg) {

}


int My::BaseApplication::Init(){
	std::cout << m_Config;
	return 0;
}


void My::BaseApplication::Destroy(){


}


void My::BaseApplication::Update(){


}

bool My::BaseApplication::IsQuit(){

	return m_bQuit;
}
