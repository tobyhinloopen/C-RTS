__kernel void square(__global float * input, __global float * output, const unsigned int count) {
  unsigned int i = get_global_id(0);
  if(i < count)
    output[i] = input[i] * input[i] * input[i] * input[i] * input[i] * input[i] * input[i] * input[i];
}

__kernel void distance_map(
  const __global float * points_x,
  const __global float * points_y,
  __global unsigned char * output_map,
  const unsigned int point_count,
  const unsigned int map_size
) {
  const unsigned int x = get_global_id(0);
  const unsigned int y = get_global_id(1);
  if (x > map_size || y > map_size) {
    return;
  }
  const float xf = (float)x;
  const float yf = (float)y;
  float closest_distance_sq = MAXFLOAT;
  for (unsigned int i = 0; i < point_count; i++) {
    const float dx = points_x[i] - xf;
    const float dy = points_y[i] - yf;
    const float current_distance_sq = dx * dx + dy * dy;
    if (current_distance_sq < closest_distance_sq) {
      closest_distance_sq = current_distance_sq;
    }
  }
  const float closest_distance = sqrt(closest_distance_sq);
  const unsigned char uc_distance = closest_distance > 255.0f ? 255 : (unsigned char)closest_distance;
  output_map[y * map_size + x] = uc_distance;
}

__kernel void closest_unit(
  const __global float2 * units,
  const __global int * team_ids,
  __global float3 * closest_enemy_units,
  __global float3 * closest_friendly_units,
  const unsigned int count
) {
  unsigned int gid = get_global_id(0);
  if (gid >= count) {
    return;
  }
  const float3 unit;
  unit.xy = units[gid];
  unit.z = MAXFLOAT;
  const int team_id = team_ids[gid];

  float3 closest_friendly_unit = unit;
  float3 closest_enemy_unit = unit;

  for (unsigned int i = 0; i < count; i++) {
    if (i == gid) {
      continue;
    }
    float3 current_unit;
    current_unit.xy = units[i];
    const float2 diff = current_unit.xy - unit.xy;
    current_unit.z = diff.x * diff.x + diff.y * diff.y;
    const int current_team_id = team_ids[i];
    if (current_team_id == team_id) {
      if (current_unit.z < closest_friendly_unit.z) {
        closest_friendly_unit = current_unit;
      }
    } else if (current_unit.z < closest_enemy_unit.z) {
      closest_enemy_unit = current_unit;
    }
  }

  closest_friendly_units[gid] = closest_friendly_unit;
  closest_enemy_units[gid] = closest_enemy_unit;
}
