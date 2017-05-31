Uniforms
{
	template Material : 0
	{
		vec3 Color;
	}
}

Attributes
{
	vec4 in_vert : 0;
	vec2 in_uv : 1;
}

Vertex
{
	void main()
	{
		gl_Position = Jwl_MVP * in_vert;
	}
}

Geometry
{
	layout(triangles) in;
	layout(line_strip, max_vertices = 4) out;

	void main()
	{
		gl_Position = gl_in[0].gl_Position;
		EmitVertex();

		gl_Position = gl_in[1].gl_Position;
		EmitVertex();

		gl_Position = gl_in[2].gl_Position;
		EmitVertex();

		gl_Position = gl_in[0].gl_Position;
		EmitVertex();

		EndPrimitive();
	}
}

Fragment
{
	out vec3 outColor;

	void main()
	{
		outColor = Material.Color;
	}
}