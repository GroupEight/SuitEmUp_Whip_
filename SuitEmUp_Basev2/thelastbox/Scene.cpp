#include "Scene.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


Scene::Scene(sf::RenderWindow& window)
/*: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, mSceneGraph()
, mSceneLayers()*/{
	loadTextures();
	buildScene();
}

void Scene::update(sf::Time dt){
	//mSceneGraph.update(dt);
}

void Scene::draw(){
	/*mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
*/}

void Scene::loadTextures(){
	//mTextures.load(Textures::TEXTUREID, "FILEPATH");
}

void Scene::buildScene(){
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i){
		//SceneNode::Ptr layer(new SceneNode());
		//mSceneLayers[i] = layer.get();

		//mSceneGraph.attachChild(std::move(layer));
	}

	// Add the SceneNode to the scene
	//std::unique_ptr<CLASS> NAME(new CLASS( CONSTRUCTOR ));
	//CLASSINSTANCE = NAME.get();
	//mSceneLayers[LAYER]->attachChild(std::move(NAME));
}