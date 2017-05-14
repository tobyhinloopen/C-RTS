require 'chunky_png'

def to_png(map_path)
  bytes = File.read(map_path).each_byte.to_a
  map_size = Math.sqrt(bytes.length).ceil
  png = ChunkyPNG::Image.new(map_size, map_size, ChunkyPNG::Color::TRANSPARENT)

  (0..(map_size-1)).each do |x|
    (0..(map_size-1)).each do |y|
      i = y * map_size + x;
      dval = bytes[i]
      pval = dval == 0 ? 255 : 0
      png[x,y] = ChunkyPNG::Color.rgb(dval + pval, dval, dval)
    end
  end

  png.save(map_path.sub(/.map$/, '.png'), interlace: true)
end

Dir["tmp/*.map"].each{|path|to_png path}
