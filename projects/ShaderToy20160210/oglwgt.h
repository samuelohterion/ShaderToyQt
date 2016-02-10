#ifndef OGLWGT_H
#define OGLWGT_H

#include <QGLWidget>
#include <QCloseEvent>
#include <GLES3/gl3.h>
#include "shaderprogram.h"
#include <QImage>
#include <QTimer>
#include "math.h"

namespace Ui {

	class OGLWgt;
}

class OGLWgt :
public QGLWidget {

		Q_OBJECT

	public:

		explicit
		OGLWgt( QWidget *p_parent = 0 );

		~OGLWgt( );

	private:

		Ui::OGLWgt
		*ui;

		QTimer
		timer;

		int
		time;

	private:

		void
		createFrameBuffers( );

		void
		createShaders( );

		void
		createTextures( );

		void
		createVertexArray( );

	public:

		void
		closeEvent( QCloseEvent *p_closeEvent );

		void
		initializeGL( );

		void
		paintGL( );

		void
		render( );

		void
		resizeGL( int p_width, int p_height );

	public slots:

		void
		slotTimerLoop( );
};

#endif // OGLWGT_H
