Uniforms
{
	template Material : 0
	{
		vec3 Color = (1, 1, 1);
		float Animation = 0.0;
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
		gl_Position = in_vert;
	}
}

Geometry
{
	layout(triangles) in;
	layout(line_strip, max_vertices = 6) out;

	uvec2 INDECES[3] = uvec2[](
		uvec2(0, 1),
		uvec2(1, 2),
		uvec2(2, 0));

	void main()
	{
		for (int i = 0; i < 3; i++)
		{
			vec3 p1 = gl_in[INDECES[i].x].gl_Position.xyz;
			vec3 p2 = gl_in[INDECES[i].y].gl_Position.xyz;
			vec3 halfway = (p1 + p2) * 0.5;

			gl_Position.xyz = mix(p1, halfway, Material.Animation);
			gl_Position.xyz *= mix(1.0, 1.5, Material.Animation);
			gl_Position = Jwl_MVP * vec4(gl_Position.xyz, 1.0);
			EmitVertex();

			gl_Position.xyz = mix(p2, halfway, Material.Animation);
			gl_Position.xyz *= mix(1.0, 1.5, Material.Animation);
			gl_Position = Jwl_MVP * vec4(gl_Position.xyz, 1.0);
			EmitVertex();

			EndPrimitive();
		}
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
