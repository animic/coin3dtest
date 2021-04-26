#include <QtWidgets/QApplication>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCube.h>

int main(int argc, char *argv[])
{

	QWidget* mainwin = SoQt::init(argc, argv, argv[0]);

	SoSeparator* root = new SoSeparator();
	root->ref();
	SoCube* cube = new SoCube();
	root->addChild(cube);

	SoQtExaminerViewer* eviwer = new SoQtExaminerViewer(mainwin);
	eviwer->setSceneGraph(root);
	eviwer->show();
	SoQt::show(mainwin);
	SoQt::mainLoop();

	root->unref();
	delete eviwer;
	return 0;
}
