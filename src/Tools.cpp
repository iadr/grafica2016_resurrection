#include "Tools.h"

void tools::debug(std::string msg,int kind){
	if(debug_mode){
		std::string fg_color="",f_color="\x1B[36m";
		std::string prefix=" [\x1B[36m--DEBUG\x1B[0m]";
		switch(kind){
			case DBG_INFO:
				prefix=" \x1B[45m\x1B[37m INF \x1B[0m ";
				fg_color="\x1B[40m";
				f_color="\x1B[35m";
			break;
			case DBG_WARNING:
			 	prefix=" \x1B[43m\x1B[37m WAR \x1B[0m ";
				fg_color="\x1B[40m";
				f_color="\x1B[33m";
			break;
			case DBG_ERROR:
				prefix=" \x1B[41m\x1B[37m ERR \x1B[0m ";
				fg_color="\x1B[40m";
				f_color="\x1B[31m";
				break;
			case DBG_MSG:
				prefix=" \x1B[42m\x1B[30m MSG \x1B[0m ";
				fg_color="\x1B[40m";
				f_color="\x1B[32m";
			break;
			case DBG_KEY_PRESSED:
				prefix=" [KEY_PRESSED] ";
				fg_color="\x1B[40m";
				f_color="\x1B[37m";
			break;
			case DBG_KEY_RELEASED:
				prefix=" [DBG_KEY_RELEASED] ";
				fg_color="\x1B[40m";
				f_color="\x1B[37m";
			break;
			default:
				break;
		}
		std::cout<<prefix<<fg_color<<f_color<<msg<<"\x1B[0m"<<std::endl;
	}
}

bool tools::load_mesh (const char* file_name, GLuint* vao, int* point_count) {
	const aiScene* scene = aiImportFile (file_name, aiProcess_Triangulate);
	if (!scene) {
		//f//printf (stderr, "ERROR: reading mesh %s\n", file_name);
		return false;
	}
	//printf ("  %i animations\n", scene->mNumAnimations);
	//printf ("  %i cameras\n", scene->mNumCameras);
	//printf ("  %i lights\n", scene->mNumLights);
	//printf ("  %i materials\n", scene->mNumMaterials);
	//printf ("  %i meshes\n", scene->mNumMeshes);
	//printf ("  %i textures\n", scene->mNumTextures);
	
	/* get first mesh in file only */
	const aiMesh* mesh = scene->mMeshes[0];
	//printf ("    %i vertices in mesh[0]\n", mesh->mNumVertices);
	
	/* pass back number of vertex points in mesh */
	*point_count = mesh->mNumVertices;
	/* generate a VAO, using the pass-by-reference parameter that we give to the
	function */
	

	glGenVertexArrays (1, vao);
	
	glBindVertexArray (*vao);
	
	/* we really need to copy out all the data from AssImp's funny little data
	structures into pure contiguous arrays before we copy it into data buffers
	because assimp's texture coordinates are not really contiguous in memory.
	i allocate some dynamic memory to do this. */
	GLfloat* points = NULL; // array of vertex points
	GLfloat* normals = NULL; // array of vertex normals
	GLfloat* texcoords = NULL; // array of texture coordinates
	if (mesh->HasPositions ()) {
		points = (GLfloat*)malloc (*point_count * 3 * sizeof (GLfloat));
		for (int i = 0; i < *point_count; i++) {
			const aiVector3D* vp = &(mesh->mVertices[i]);
			points[i * 3] = (GLfloat)vp->x;
			points[i * 3 + 1] = (GLfloat)vp->y;
			points[i * 3 + 2] = (GLfloat)vp->z;
		}
	}
	if (mesh->HasNormals ()) {
		normals = (GLfloat*)malloc (*point_count * 3 * sizeof (GLfloat));
		for (int i = 0; i < *point_count; i++) {
			const aiVector3D* vn = &(mesh->mNormals[i]);
			normals[i * 3] = (GLfloat)vn->x;
			normals[i * 3 + 1] = (GLfloat)vn->y;
			normals[i * 3 + 2] = (GLfloat)vn->z;
		}
	}
	if (mesh->HasTextureCoords (0)) {
		texcoords = (GLfloat*)malloc (*point_count * 2 * sizeof (GLfloat));
		for (int i = 0; i < *point_count; i++) {
			const aiVector3D* vt = &(mesh->mTextureCoords[0][i]);
			texcoords[i * 2] = (GLfloat)vt->x;
			texcoords[i * 2 + 1] = (GLfloat)vt->y;
		}
	}
	/* copy mesh data into VBOs */
	if (mesh->HasPositions ()) {
		GLuint vbo;
		glGenBuffers (1, &vbo);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		glBufferData (
			GL_ARRAY_BUFFER,
			3 * *point_count * sizeof (GLfloat),
			points,
			GL_STATIC_DRAW
		);
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray (0);
		free (points);
	}
	if (mesh->HasNormals ()) {
		GLuint vbo;
		glGenBuffers (1, &vbo);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		glBufferData (
			GL_ARRAY_BUFFER,
			3 * *point_count * sizeof (GLfloat),
			normals,
			GL_STATIC_DRAW
		);
		glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray (1);
		free (normals);
	}
	if (mesh->HasTextureCoords (0)) {
		GLuint vbo;
		glGenBuffers (1, &vbo);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);
		glBufferData (
			GL_ARRAY_BUFFER,
			2 * *point_count * sizeof (GLfloat),
			texcoords,
			GL_STATIC_DRAW
		);
		glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray (2);
		free (texcoords);
	}
	if (mesh->HasTangentsAndBitangents ()) {
		// NB: could store/print tangents here
	}
	
	aiReleaseImport (scene);
	//printf ("mesh loaded\n");
	
	return true;
}
