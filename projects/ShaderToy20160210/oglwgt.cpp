#include "oglwgt.h"
#include "ui_oglwgt.h"

OGLWgt::OGLWgt( QWidget *p_parent ) :
QGLWidget( p_parent ),
ui( new Ui::OGLWgt ) {

	ui->setupUi( this );

	connect( &timer, SIGNAL( timeout( ) ), this, SLOT( slotTimerLoop( ) ) );

	timer.setInterval( 1000. / 30. );
}

OGLWgt::~OGLWgt( ) {

	delete ui;
}

void OGLWgt::createFrameBuffers( ) {

}




void
ParticleSimulation::closeEvent( QCloseEvent *p_closeEvent ) {

	p_closeEvent->accept( );
}

void
ParticleSimulation::createFrameBuffers( ) {

//	//generate Framebuffer for Differentiation
	glGenFramebuffers( 1, &simFBO_Diff_Id );

//	// configure Framebuffer 1
//	glBindFramebuffer( GL_FRAMEBUFFER, simFBO_Diff_Id );

//	glActiveTexture( GL_TEXTURE0 );
//	glBindTexture( GL_TEXTURE_2D, simTEX_K_hxy_D_Id );

//	glActiveTexture( GL_TEXTURE1 );
//	glBindTexture( GL_TEXTURE_2D, simTEX_H_HDot_Id );

//	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, simTEX_HDot_HDotDot_Id, 0 );
//	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, simTEX_HDot_HDotDot_RG_Sum_Id, 0 );

//	GLenum const
//	drawBuffersDiff[ 2 ] = {

//		GL_COLOR_ATTACHMENT0,
//		GL_COLOR_ATTACHMENT1
//	};

//	glDrawBuffers( 2, drawBuffersDiff );

//	GLenum
//	fboStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );

//	if( fboStatus != GL_FRAMEBUFFER_COMPLETE ) {

//		switch( fboStatus ) {

//			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT : {

//				std::cout << "framebuffer incomplete attachment" << std::endl;
//				break;
//			}
//			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS : {

//				std::cout << "framebuffer incomplete dimensions" << std::endl;
//				break;
//			}
//			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT : {

//				std::cout << "framebuffer incomplete missing attachment" << std::endl;
//				break;
//			}
//			case GL_FRAMEBUFFER_UNSUPPORTED : {

//				std::cout << "framebuffer unsupported" << std::endl;
//				break;
//			}
//			default:

//				std::cout << "framebuffer incomplete" << std::endl;
//				break;
//		}
//	}

//	// generate Framebuffer for integration
	glGenFramebuffers( 1, &simFBO_Intg_Id );

//	// configure Framebuffer 1
//	glBindFramebuffer( GL_FRAMEBUFFER, simFBO_Intg_Id );

//	glActiveTexture( GL_TEXTURE0 );
//	glBindTexture( GL_TEXTURE_2D, simTEX_K_hxy_D_Id );

//	glActiveTexture( GL_TEXTURE1 );
//	glBindTexture( GL_TEXTURE_2D, simTEX_H_HDot_Id );

//	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, simTEX_HDot_HDotDot_Id, 0 );

//	GLenum const
//	drawBuffersIntg[ 1 ] = {

//		GL_COLOR_ATTACHMENT0
//	};

//	glDrawBuffers( 1, drawBuffersIntg );

//	fboStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );

//	if( fboStatus != GL_FRAMEBUFFER_COMPLETE ) {

//		switch( fboStatus ) {

//			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT : {

//				std::cout << "framebuffer incomplete attachment" << std::endl;
//				break;
//			}
//			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS : {

//				std::cout << "framebuffer incomplete dimensions" << std::endl;
//				break;
//			}
//			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT : {

//				std::cout << "framebuffer incomplete missing attachment" << std::endl;
//				break;
//			}
//			case GL_FRAMEBUFFER_UNSUPPORTED : {

//				std::cout << "framebuffer unsupported" << std::endl;
//				break;
//			}
//			default:

//				std::cout << "framebuffer incomplete" << std::endl;
//				break;
//		}
//	}

//	glBindTexture( GL_TEXTURE_2D, 0 );
//	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

}

void
ParticleSimulation::createShaders( ) {

	simShaderDifferentiatorFirst = new ShaderProgram(

		//Vertex Shader
		"#version 130\n"

		"in highp vec2\n"
		"inVPos,\n"
		"inTPos;\n"

		"uniform highp float\n"
		"dx,\n"
		"dy;\n"

		"varying highp vec2\n"
		"texPos;\n"

		"void\n"
		"main( ) {\n"

		"	gl_Position = vec4( 0. * vec2( dx, dy ) + inVPos, 0., 1. );\n"
		"	texPos = inTPos;\n"

		"}\n",
		//Fragment Shader

		"#version 130\n"

		"uniform highp sampler2D\n"
		"tex_K_hxy_D,\n"
		"tex_H_HDot,\n"
		"tex_HDot_HDotDot_RG_Sum;\n"

		"uniform highp float\n"
		"sumFactor,\n"
		"dx,\n"
		"dy;\n"

		"varying highp vec2\n"
		"texPos;\n"

		"out highp vec2\n"
		"col[ 2 ];\n"

		"void\n"
		"main( ) {\n"

		"	highp float\n"
		"	h   = texture2D( tex_H_HDot, texPos ).r,\n"
		"	vel = texture2D( tex_H_HDot, texPos ).g,\n"
		"	hxn = texture2D( tex_H_HDot, texPos + vec2( -dx,  0. ) ).r - h,\n"
		"	hxp = texture2D( tex_H_HDot, texPos + vec2( +dx,  0. ) ).r - h,\n"
		"	hyn = texture2D( tex_H_HDot, texPos + vec2(  0., -dy ) ).r - h,\n"
		"	hyp = texture2D( tex_H_HDot, texPos + vec2(  0., +dy ) ).r - h,\n"
		"	kh  = texture2D( tex_K_hxy_D, texPos ).r,\n"
		"	kxn = .5 * ( texture2D( tex_K_hxy_D, texPos + vec2( -dx,  0. ) ).g + kh ),\n"
		"	kyn = .5 * ( texture2D( tex_K_hxy_D, texPos + vec2(  0., -dy ) ).b + kh ),\n"
		"	kxp = .5 * ( texture2D( tex_K_hxy_D, texPos + vec2( +dx,  0. ) ).g + kh ),\n"
		"	kyp = .5 * ( texture2D( tex_K_hxy_D, texPos + vec2(  0., +dy ) ).b + kh ),\n"
		"	dmp = texture2D( tex_K_hxy_D, texPos ).a,\n"
//		"	acc = -kh * h + ( + kxn * hxn + kyn * hyn + kxp * hxp + kyp * hyp ) - dmp * vel;\n"
		"	acc = -kh * h + ( + kxn * hxn + kyn * hyn + kxp * hxp + kyp * hyp ) - dmp * vel;\n"

		"	col[ 0 ].r = vel;\n"
		"	col[ 0 ].g = acc;\n"
		"	col[ 1 ].r = sumFactor * vel;\n"
		"	col[ 1 ].g = sumFactor * acc;\n"

		"}\n",

		Shader::FROM_CODE
	);

	simShaderDifferentiator = new ShaderProgram(

		//Vertex Shader
		"#version 130\n"

		"in highp vec2\n"
		"inVPos,\n"
		"inTPos;\n"

		"uniform highp float\n"
		"dx,\n"
		"dy;\n"

		"varying highp vec2\n"
		"texPos;\n"

		"void\n"
		"main( ) {\n"

		"	gl_Position = vec4( 0. * vec2( dx, dy ) + inVPos, 0., 1. );\n"
		"	texPos      = +0. * vec2( dx, dy ) + inTPos;\n"

		"}\n",

		//Fragment Shader
		"#version 130\n"

		"uniform highp sampler2D\n"
		"tex_K_hxy_D,\n"
		"tex_H_HDot,\n"
		"tex_HDot_HDotDot_RG_Sum;\n"

		"uniform highp float\n"
		"sumFactor,\n"
		"dx,\n"
		"dy;\n"

		"varying highp vec2\n"
		"texPos;\n"

		"out highp vec2\n"
		"col[ 2 ];\n"

		"void\n"
		"main( ) {\n"

		"	highp float\n"
		"	h   = texture2D( tex_H_HDot, texPos ).r,\n"
		"	vel = texture2D( tex_H_HDot, texPos ).g,\n"
		"	hxn = texture2D( tex_H_HDot, texPos + vec2( -dx,  0. ) ).r - h,\n"
		"	hxp = texture2D( tex_H_HDot, texPos + vec2( +dx,  0. ) ).r - h,\n"
		"	hyn = texture2D( tex_H_HDot, texPos + vec2(  0., -dy ) ).r - h,\n"
		"	hyp = texture2D( tex_H_HDot, texPos + vec2(  0., +dy ) ).r - h,\n"
		"	kh  = texture2D( tex_K_hxy_D, texPos ).r,\n"
		"	kxn = .5 * ( texture2D( tex_K_hxy_D, texPos + vec2( -dx,  0. ) ).g + kh ),\n"
		"	kyn = .5 * ( texture2D( tex_K_hxy_D, texPos + vec2(  0., -dy ) ).b + kh ),\n"
		"	kxp = .5 * ( texture2D( tex_K_hxy_D, texPos + vec2( +dx,  0. ) ).g + kh ),\n"
		"	kyp = .5 * ( texture2D( tex_K_hxy_D, texPos + vec2(  0., +dy ) ).b + kh ),\n"
		"	dmp = texture2D( tex_K_hxy_D, texPos ).a,\n"
		"	acc = -kh * h + ( + kxn * hxn + kyn * hyn + kxp * hxp + kyp * hyp ) - dmp * vel;\n"

		"	col[ 0 ].r = vel;\n"
		"	col[ 0 ].g = acc;\n"
		"	col[ 1 ].r = texture2D( tex_HDot_HDotDot_RG_Sum, texPos - .0 * vec2( dx, dy ) ).r + sumFactor * vel;\n"
		"	col[ 1 ].g = texture2D( tex_HDot_HDotDot_RG_Sum, texPos - .0 * vec2( dx, dy ) ).g + sumFactor * acc;\n"

		"}\n",

		Shader::FROM_CODE
	);

	simShaderIntegrator = new ShaderProgram(

		//Vertex Shader
		"#version 130\n"

		"in highp vec2\n"
		"inVPos,\n"
		"inTPos;\n"

		"uniform highp float\n"
		"dx,\n"
		"dy;\n"

		"varying highp vec2\n"
		"texPos;\n"

		"void\n"
		"main( ) {\n"

		"	gl_Position = vec4( 0.5 * vec2( dx, dy ) + inVPos, 0., 1. );\n"
		"	texPos = 0. * vec2( dx, dy ) + inTPos;\n"

		"}\n",

		//Fragment Shader
		"#version 130\n"

		"uniform highp sampler2D\n"
		"tex_H_HDot,\n"
		"tex_HDot_HDotDot;\n"

		"uniform highp float\n"
		"dt,\n"
		"dx,\n"
		"dy;\n"

		"varying highp vec2\n"
		"texPos;\n"

		"out highp vec2\n"
		"colOut_H_HDot;\n"

		"void\n"
		"main( ) {\n"

		"	highp float\n"
		"	hCurr    = texture2D( tex_H_HDot, texPos ).r,\n"
		"	hDotCurr = texture2D( tex_H_HDot, texPos ).g,\n"
		"	hDot     = texture2D( tex_HDot_HDotDot, texPos ).r,\n"
		"	hDotDot  = texture2D( tex_HDot_HDotDot, texPos ).g;\n"

		"	colOut_H_HDot.r = hCurr + dt * hDot;\n"
		"	colOut_H_HDot.g = hDotCurr + dt * hDotDot;\n"

		"}\n",

		Shader::FROM_CODE
	);

		viewShader = new ShaderProgram(

			//Vertex Shader
			"#version 130\n"

			"uniform float\n"
			"dx,\n"
			"dy;\n"

			"in vec2\n"
			"inVPos,\n"
			"inTPos;\n"

			"varying vec2\n"
			"texPos;\n"

			"void\n"
			"main( ) {\n"

			"	gl_Position = vec4( 0.5 * vec2( dx, dy ) + inVPos, 0., 1. );\n"
			"	texPos = inTPos;\n"

			"}\n",

			//Fragment Shader
			"#version 130\n"

			"uniform sampler2D\n"
			"tex_K_hxy_D,\n"
			"tex_H_HDot;\n"

			"uniform float\n"
			"dx,\n"
			"dy;\n"

			"varying vec2\n"
			"texPos;\n"

			"out vec4\n"
			"col;\n"

			"void\n"
			"main( ) {\n"

			"	float\n"
			"	h    = texture2D( tex_H_HDot, texPos ).r,\n"
			"	hdot = texture2D( tex_H_HDot, texPos ).g,\n"
			"	kh   = texture2D( tex_K_hxy_D, texPos ).r,\n"
			"	kx   = texture2D( tex_K_hxy_D, texPos ).g,\n"
			"	ky   = texture2D( tex_K_hxy_D, texPos ).b,\n"
			"	d    = texture2D( tex_K_hxy_D, texPos ).a,\n"
			"	f    = - .005 * ( kh + 1. * kx + 1. * ky );\n"

			"	if( h < 0. ) {\n"

			"		col = min( vec4( 1. ), max( vec4( 0. ), vec4( f - 1. * h, f, f, 1. ) ) );\n"
			"	}\n"
			"	else {\n"

			"		col = min( vec4( 1. ), max( vec4( 0. ), vec4( f, f + 1. * h, f + 1. * h, 1. ) ) );\n"
			"	}\n"
			"	col = min( vec4( 1. ), max( vec4( 0. ), vec4( .5 + f + 1.5 * h, .5 + f + 1.5 * h, .5 + f, 1. ) ) );\n"
			"}\n",

			Shader::FROM_CODE
		);


/*
		viewShader = new ShaderProgram(

			//Vertex Shader
			"#version 130\n"

			"uniform float\n"
			"dx,\n"
			"dy;\n"

			"in vec2\n"
			"inVPos,\n"
			"inTPos;\n"

			"varying vec2\n"
			"texPos;\n"

			"void\n"
			"main( ) {\n"

			"	gl_Position = vec4( 0.5 * vec2( dx, dy ) + inVPos, 0., 1. );\n"
			"	texPos = inTPos;\n"

			"}\n",

			//Fragment Shader
			"#version 130\n"

			"uniform sampler2D\n"
			"tex_K_hxy_D,\n"
			"tex_H_HDot;\n"

			"uniform float\n"
			"dx,\n"
			"dy;\n"

			"varying vec2\n"
			"texPos;\n"

			"out vec4\n"
			"col;\n"

			"void\n"
			"main( ) {\n"

			"	float\n"
			"	h    = texture2D( tex_H_HDot, texPos ).r,\n"
			"	hdot = texture2D( tex_H_HDot, texPos ).g,\n"
			"	kh   = texture2D( tex_K_hxy_D, texPos ).r,\n"
			"	kx = texture2D( tex_K_hxy_D, texPos ).g,\n"
			"	ky = texture2D( tex_K_hxy_D, texPos ).b,\n"
			"	d  = texture2D( tex_K_hxy_D, texPos ).a,\n"
			"	f  = .01 * ( kh + 1. * kx + 1. * ky );\n"

	//		"	col = vec4( k + x, kx + v, ky - d, 1 );\n"
	//		"	col = texture2D( tex_H_HDot, texPos ).rgrg;\n"
	//		"	col = texture2D( tex_K_hxy_D, texPos ).rgrg;\n"
			"	col= min( vec4( 1. ), max( vec4( 0. ), vec4( f + ( .5 + 2.5 * h ), f + ( .5 + 2.5 * hdot ), f + ( .5 + 1.25 * ( h + hdot ) ), 1. ) ) );\n"

			"}\n",

			Shader::FROM_CODE
		);
*/

/*
	viewShader = new ShaderProgram(

		//Vertex Shader
		"#version 130\n"

		"uniform highp float\n"
		"dx,\n"
		"dy;\n"

		"in highp vec2\n"
		"inVPos,\n"
		"inTPos;\n"

		"varying highp vec2\n"
		"texPos;\n"

		"void\n"
		"main( ) {\n"

		"	gl_Position = vec4( 0.5 * vec2( dx, dy ) + inVPos, 0., 1. );\n"
		"	texPos = inTPos;\n"

		"}\n",

		//Fragment Shader
		"#version 130\n"

		"uniform highp sampler2D\n"
		"tex_K_hxy_D,\n"
		"tex_H_HDot;\n"

		"uniform highp float\n"
		"dx,\n"
		"dy;\n"

		"varying highp vec2\n"
		"texPos;\n"

		"out highp vec4\n"
		"col;\n"

		"void\n"
		"main( ) {\n"

		"	highp float\n"
		"	gr =  -2. * texture( tex_H_HDot, texPos + vec2( -dx, -dy ) ).r - 1. * texture( tex_H_HDot, texPos + vec2( 0., -dy ) ).r + 0. * texture( tex_H_HDot, texPos + vec2( +dx, -dy ) ).r +\n"
		"		  -1. * texture( tex_H_HDot, texPos + vec2( -dx,  0. ) ).r + 0. * texture( tex_H_HDot, texPos + vec2( 0.,  0. ) ).r + 1. * texture( tex_H_HDot, texPos + vec2( +dx,  0. ) ).r +\n"
		"	       0. * texture( tex_H_HDot, texPos + vec2( -dx, +dy ) ).r + 1. * texture( tex_H_HDot, texPos + vec2( 0., +dy ) ).r + 2. * texture( tex_H_HDot, texPos + vec2( +dx, +dy ) ).r;\n"
		"	gr = 0.75 + 0.25 * gr;\n"
		"	gr = .5;// * max( 0., min( 1., gr ) );\n"

		"	highp float\n"
		"	r = .3 * ( 1 + 5. * texture2D( tex_H_HDot, texPos ).r ),\n"
		"	g = 1 + 5. * texture2D( tex_H_HDot, texPos ).g,\n"
		"	b = 0.02 * ( texture2D( tex_K_hxy_D, texPos ).r );\n"
		"	col.rgba = min( vec4( 1. ), max( vec4( 0 ), vec4( gr * ( b + 1. * r ), gr * ( b + 1. * r ), gr * ( b + g ), 1. ) ) );\n"
		"	if( 0.5 - dx < texPos.s &&  texPos.s < 0.5 + dx && 0.5 -dx < texPos.t && texPos.t < 0.5 + dy ) {\n"
		"		col.rgba = vec4( 0. );\n"
		"	}\n"

		"}\n",

		Shader::FROM_CODE
	);
*/
}

void
ParticleSimulation::createTextures( ) {

	// Erstelle Textur fuer Simulation
	glGenTextures( 1, &simTEX_K_hxy_D_Id );

	// Konfiguriere Simulation Textur
	glBindTexture( GL_TEXTURE_2D, simTEX_K_hxy_D_Id );
	glTexStorage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, simWidth, simHeight );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, simWidth, simHeight, 0, GL_RGBA, GL_FLOAT, k_hxy_d.data( ) );

	// Erstelle Texturen fuer Simulation

	// Erstelle Textur simTEX_X_XDot_Id
	glGenTextures( 1, &simTEX_H_HDot_Id );

	// Konfiguriere Textur simTEX_X_XDot_Id
	glBindTexture( GL_TEXTURE_2D, simTEX_H_HDot_Id );
	glTexStorage2D( GL_TEXTURE_2D, 0, GL_RG32F, simWidth, simHeight );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RG32F, simWidth, simHeight, 0, GL_RG, GL_FLOAT, h_hdot.data( ) );

	// Erstelle Textur simTEX_H_HDot_IS_Id
	glGenTextures( 1, &simTEX_H_HDot_IS_Id );

	// Konfiguriere Textur simTEX_H_HDot_IS_Id
	glBindTexture( GL_TEXTURE_2D, simTEX_H_HDot_IS_Id );
	glTexStorage2D( GL_TEXTURE_2D, 0, GL_RG32F, simWidth, simHeight );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RG32F, simWidth, simHeight, 0, GL_RG, GL_FLOAT, 0 );

	// Erstelle Textur simTEX_HDot_HDotDot_Id
	glGenTextures( 1, &simTEX_HDot_HDotDot_Id );

	// Konfiguriere Textur simTEX_HDot_HDotDot_Id
	glBindTexture( GL_TEXTURE_2D, simTEX_HDot_HDotDot_Id );
	glTexStorage2D( GL_TEXTURE_2D, 0, GL_RG32F, simWidth, simHeight );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RG32F, simWidth, simHeight, 0, GL_RG, GL_FLOAT, 0 );

	// Erstelle Textur simTEX_HDot_HDotDot_RG_Sum_Id
	glGenTextures( 1, &simTEX_HDot_HDotDot_RG_Sum_Id );

	// Konfiguriere Textur simTEX_HDot_HDotDot_RG_Sum_Id
	glBindTexture( GL_TEXTURE_2D, simTEX_HDot_HDotDot_RG_Sum_Id );
	glTexStorage2D( GL_TEXTURE_2D, 0, GL_RG32F, simWidth, simHeight );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RG32F, simWidth, simHeight, 0, GL_RG, GL_FLOAT, 0 );

	glBindTexture( GL_TEXTURE_2D, 0 );
}

void
ParticleSimulation::createVertexArray( ) {

	static const GLfloat
	viewVertPosAndTexPos[ ]	= {

		-1., -1.,	0., 0.,
		+1., -1.,	1.,	0.,
		+1., +1.,	1., 1.,
		-1., +1.,	0., 1.
	};

	static const GLfloat
	simVertPosAndTexPos[ ]	= {

		-1., -1.,	0., 0.,
		+1., -1.,	1.,	0.,
		+1., +1.,	1., 1.,
		-1., +1.,	0., 1.
	};

	glGenVertexArrays( 1, &simVAOId );
	glBindVertexArray( simVAOId );

	glGenBuffers( 1, &simVBOId );
	glBindBuffer( GL_ARRAY_BUFFER, simVBOId );
	glBufferData( GL_ARRAY_BUFFER, sizeof( simVertPosAndTexPos ), simVertPosAndTexPos, GL_STATIC_DRAW );

	simShaderDifferentiator->bind( );
//	simShaderDifferentiator->setUniformInt( "tex_K_hxy_D", 0 );
//	simShaderDifferentiator->setUniformInt( "tex_H_HDot", 1 );
	simShaderDifferentiator->setVertexAttrib( "inVPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 0 * sizeof( GLfloat ) ) );
	simShaderDifferentiator->setVertexAttrib( "inTPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 2 * sizeof( GLfloat ) ) );
	simShaderDifferentiator->release( );

	simShaderIntegrator->bind( );
//	simShaderIntegrator->setUniformInt( "tex_K_hxy_D", 0 );
//	simShaderIntegrator->setUniformInt( "tex_H_HDot", 1 );
	simShaderIntegrator->setVertexAttrib( "inVPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 0 * sizeof( GLfloat ) ) );
	simShaderIntegrator->setVertexAttrib( "inTPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 2 * sizeof( GLfloat ) ) );
	simShaderIntegrator->release( );


	glGenVertexArrays( 1, &viewVAOId );
	glBindVertexArray( viewVAOId );

	glGenBuffers( 1, &viewVBOId );
	glBindBuffer( GL_ARRAY_BUFFER, viewVBOId );
	glBufferData( GL_ARRAY_BUFFER, sizeof( viewVertPosAndTexPos ), viewVertPosAndTexPos, GL_STATIC_DRAW );

	viewShader->bind( );
//	viewShader->setUniformInt( "tex_BC", 0 );
//	viewShader->setUniformInt( "tex_X_XDot", 1 );
	viewShader->setVertexAttrib( "inVPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 0 * sizeof( GLfloat ) ) );
	viewShader->setVertexAttrib( "inTPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 2 * sizeof( GLfloat ) ) );
	viewShader->release( );

	glBindBuffer( GL_VERTEX_ARRAY, 0 );
	glBindVertexArray( 0 );
}

void
OGLWgt::initializeGL( ) {

	glFrustum( 0., 1., 0., 1., 0., 0. );

	createShaders( );

	createTextures( );

	createVertexArray( );

	createFrameBuffers( );

	glClearColor( 1., 1., 1., 1. );

//	glDisable( GL_BLEND );

	timer.start( );
}

void
OGLWgt::paintGL( ) {

	renderSimulation( );

	int
	y = simHeight / 2,
	x = simWidth / 2,
	id = ( y * simWidth + x ) * 2;
	std::cout << std::setw( 15 ) << h_hdot[ id + 0 ] << std::setw( 15 ) << h_hdot[ id + 1 ] << std::endl;
}

void
ParticleSimulation::computeDifferentiation( ShaderProgram *p_shaderProgram, GLuint const &p_src_simTex_H_HDot, GLfloat const &p_sumFactor ) {

	GLenum const
	drawBuffersDiff[ 2 ] = {

		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1
	};

	glBindFramebuffer( GL_FRAMEBUFFER, simFBO_Diff_Id );
	p_shaderProgram->bind( );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, simTEX_K_hxy_D_Id );
	p_shaderProgram->setUniformInt( "tex_K_hxy_D", 0 );

	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, p_src_simTex_H_HDot );
	p_shaderProgram->setUniformInt( "tex_H_HDot", 1 );

	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, simTEX_HDot_HDotDot_RG_Sum_Id );
	p_shaderProgram->setUniformInt( "tex_HDot_HDotDot_RG_Sum", 2 );

	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, simTEX_HDot_HDotDot_Id, 0 );
	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, simTEX_HDot_HDotDot_RG_Sum_Id, 0 );

	p_shaderProgram->setUniformFloat( "sumFactor", p_sumFactor );
	p_shaderProgram->setUniformFloat( "dx", simDx );
	p_shaderProgram->setUniformFloat( "dy", simDy );

	glBindVertexArray( simVAOId );

	glDrawBuffers( 2, drawBuffersDiff );

	GLenum
	fboStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );

	if( fboStatus != GL_FRAMEBUFFER_COMPLETE ) {

		switch( fboStatus ) {

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT : {

				std::cout << "framebuffer incomplete attachment" << std::endl;
				break;
			}
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS : {

				std::cout << "framebuffer incomplete dimensions" << std::endl;
				break;
			}
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT : {

				std::cout << "framebuffer incomplete missing attachment" << std::endl;
				break;
			}
			case GL_FRAMEBUFFER_UNSUPPORTED : {

				std::cout << "framebuffer unsupported" << std::endl;
				break;
			}
			default:

				std::cout << "framebuffer incomplete" << std::endl;
				break;
		}
	}

	glDrawArrays( GL_QUADS, 0, 4 );

	//glGetTexImage( GL_TEXTURE_2D, 0, GL_RG, GL_FLOAT, h_hdot.data( ) );

	p_shaderProgram->release( );

	glBindVertexArray( 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void
ParticleSimulation::computeIntegration( ShaderProgram *p_shaderProgram, GLuint const &p_dst_simTEX_H_HDot_Id, GLfloat const &p_deltaT, GLuint const &p_src_simTEX_HDot_HDotDot_Id ) {

	GLenum const
	drawBuffersIntg[ 1 ] = {

		GL_COLOR_ATTACHMENT0
	};

	glBindFramebuffer( GL_FRAMEBUFFER, simFBO_Intg_Id );

	p_shaderProgram->bind( );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, simTEX_H_HDot_Id );
	p_shaderProgram->setUniformInt( "tex_H_HDot", 0 );

	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, p_src_simTEX_HDot_HDotDot_Id );
	p_shaderProgram->setUniformInt( "tex_HDot_HDotDot", 1 );

	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, p_dst_simTEX_H_HDot_Id, 0 );

	p_shaderProgram->setUniformFloat( "dt", p_deltaT );
	p_shaderProgram->setUniformFloat( "dx", simDx );
	p_shaderProgram->setUniformFloat( "dy", simDy );

	glBindVertexArray( simVAOId );
	glDrawBuffers( 1, drawBuffersIntg );

	GLenum
	fboStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );

	if( fboStatus != GL_FRAMEBUFFER_COMPLETE ) {

		switch( fboStatus ) {

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT : {

				std::cout << "framebuffer incomplete attachment" << std::endl;
				break;
			}
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS : {

				std::cout << "framebuffer incomplete dimensions" << std::endl;
				break;
			}
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT : {

				std::cout << "framebuffer incomplete missing attachment" << std::endl;
				break;
			}
			case GL_FRAMEBUFFER_UNSUPPORTED : {

				std::cout << "framebuffer unsupported" << std::endl;
				break;
			}
			default:

				std::cout << "framebuffer incomplete" << std::endl;
				break;
		}
	}

	glDrawArrays( GL_QUADS, 0, 4 );

	p_shaderProgram->release( );

	glBindVertexArray( 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void
ParticleSimulation::computeSimulation( ) {


	glViewport( 0, 0, simWidth, simHeight );

	glEnable( GL_TEXTURE_2D );

	//	differentiate dH0 / dt		dV0 / dt
	//	arg1: simShaderDifferentiatorFirst			shader to use
	//	arg2: simTEX_H_HDot_Id						differentiate this!
	//	res1: simTEXHDot_HDotDot_Id					r = dH0 / dt   g = dV0 / dt
	//	res2: simTEXHDot_HDotDot_RG_Sum_Id			r = dH0 / dt   g = dV0 / dt

	computeDifferentiation( simShaderDifferentiatorFirst, simTEX_H_HDot_Id, 1. );

	//	integrate H1 = H0 + 0.5 * dt * dH0 / dt		V1 = V0 + 0.5 * dt * dV0 / dt
	//	arg1: simShaderIntegrator					shader to use
	//	arg2: simTEX_H_HDot_IS_Id					integrate into this
	//	arg3: 0.5 * dt								size of runge kutta time step
	//	arg4: simTEX_HDot_HDotDot_Id				r = dH0 / dt   g = dV0 / dt
	//  res1: simTEX_H_HDot_IS_Id					r = H1 = H0 + 0.5 * dt * dH1 / dt   g = V1 = 0.5 * dt * dV0 / dt ( inter state 1 )

	computeIntegration( simShaderIntegrator, simTEX_H_HDot_IS_Id, .5 * deltaT, simTEX_HDot_HDotDot_Id );

	//	differentiate dH1 / dt		dV1 / dt
	//	arg1:    simShaderDifferentiator			shader to use
	//	arg2:    simTEX_H_HDot_Id					differentiate this!
	//	result1: simTEXHDot_HDotDot_Id				r = dH1 / dt   g = dV1 / dt
	//	result2: simTEXHDot_HDotDot_RG_Sum_Id		r = dH0 / dt + 2 * ( dH1 / dt )   g = dV0 / dt + 2 * ( dV1 / dt )

	computeDifferentiation( simShaderDifferentiator, simTEX_H_HDot_IS_Id, 2. );

	//	integrate H2 = H0 + 0.5 * dt * dH1 / dt		V2 = V0 + 0.5 * dt * dV1 / dt
	//	arg1: simShaderIntegrator					shader to use
	//	arg2: simTEX_H_HDot_IS_Id					integrate into this
	//	arg3: 0.5 * dt								size of runge kutta time step
	//	arg4: simTEX_HDot_HDotDot_Id				r = dH1 / dt   g = dV1 / dt
	//  res1: simTEX_H_HDot_IS_Id					r = H2 = H0 + 0.5 * dt   g = V1 = 0.5 * dt ( inter state 1 )

	computeIntegration( simShaderIntegrator, simTEX_H_HDot_IS_Id, .5 * deltaT, simTEX_HDot_HDotDot_Id );

//	render differentiation H3

	computeDifferentiation( simShaderDifferentiator, simTEX_H_HDot_IS_Id, 2. );

//	render integration H3

	computeIntegration( simShaderIntegrator, simTEX_H_HDot_IS_Id, 1. * deltaT, simTEX_HDot_HDotDot_Id );

//	render differentiation H4

	computeDifferentiation( simShaderDifferentiator, simTEX_H_HDot_IS_Id, 1. );

//	render integration H4

	computeIntegration( simShaderIntegrator, simTEX_H_HDot_Id, deltaT / 6., simTEX_HDot_HDotDot_RG_Sum_Id );



//	computeDifferentiation( simShaderDifferentiatorFirst, simTEX_H_HDot_Id, 1. );
//	computeIntegration( simShaderIntegrator, simTEX_H_HDot_Id, deltaT, simTEX_HDot_HDotDot_Id );

//	computeDifferentiation( simShaderDifferentiatorFirst, simTEX_H_HDot_Id, 1. );
//	computeIntegration( simShaderIntegrator, simTEX_H_HDot_IS_Id, deltaT, simTEX_HDot_HDotDot_Id );

//	computeDifferentiation( simShaderDifferentiator, simTEX_H_HDot_Id, 1. );
//	computeIntegration( simShaderIntegrator, simTEX_H_HDot_Id, .5 * deltaT, simTEX_HDot_HDotDot_RG_Sum_Id );


	glDisable( GL_TEXTURE_2D );
}

void
ParticleSimulation::renderSimulation( ) {

	glViewport( 0, 0, viewWidth, viewHeight );

	glEnable( GL_TEXTURE_2D );
//	glDisable( GL_BLEND );

	viewShader->bind( );
	viewShader->setUniformFloat( "dx", viewDx );
	viewShader->setUniformFloat( "dy", viewDy );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, simTEX_K_hxy_D_Id );
	viewShader->setUniformInt( "tex_K_hxy_D", 0 );

	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, simTEX_H_HDot_Id );
	viewShader->setUniformInt( "tex_H_HDot", 1 );


	glBindVertexArray( viewVAOId );


	glDrawArrays( GL_QUADS, 0, 4 );

	glBindVertexArray( 0 );

	viewShader->release( );

	glBindTexture( GL_TEXTURE_2D, 0 );

	glDisable( GL_TEXTURE_2D );
}

void
ParticleSimulation::resizeGL( int p_width, int p_height ) {

	viewWidth = p_width;
	viewHeight = p_height;

	viewDx = 1. / viewWidth;
	viewDy = 1. / viewHeight;
}

void
ParticleSimulation::slotTimerLoop( ) {

	++time;

	for( int i = 0; i < 5; ++i ) {

		computeSimulation( );
	}

	updateGL( );
}
