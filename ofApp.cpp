#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1);

	this->gon = 10;
	for (auto i = 0; i < this->gon; i++) { this->gap_list.push_back(0); }

	ofColor color;
	vector<int> hex_list = { 0x247BA0, 0x70C1B3, 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(139);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int x = 210; x < ofGetWidth(); x += 300) {

		for (int y = 210; y < ofGetHeight(); y += 300) {

			auto next_random_seed = ofRandom(1000);

			for (auto& gap : this->gap_list) {

				gap = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.003), 0, 1, 0.01, 0.3);
			}

			ofPushMatrix();
			ofTranslate(x, y);
			ofRotate(ofRandom(360));

			auto radius = 130;
			int deg_span = 360 / this->gon;
			vector<glm::vec2> vertices;
			auto first = true;
			while (true) {

				if (first) {

					for (auto deg = 0; deg < 360; deg += deg_span) {

						vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
					}

					first = false;
				}
				else {

					vector<glm::vec2> tmp;
					for (auto k = 0; k < vertices.size(); k++) {

						tmp.push_back(vertices[k] + (vertices[(k + 1) % vertices.size()] - vertices[k]) * this->gap_list[k]);
					}
					vertices = tmp;
				}

				ofSetColor(ofMap(glm::distance(vertices[0], vertices[1]), 100, 1, 0, 255));
				ofFill();
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				ofSetColor(ofMap(glm::distance(vertices[0], vertices[1]), 100, 1, 255, 0));
				ofNoFill();
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				if (glm::distance(vertices[0], vertices[1]) < 1) {

					break;
				}
			}

			ofPopMatrix();
			ofSeedRandom(next_random_seed);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}