
struct xyz{
   int xz;
   int y;
};

xyz move(xyz now, xyz direction)
{
  xyz next = {now.xz + direction.xz,now.y + direction.y};
  
  return next;
}

bool valid(xyz now, xyz direction){
    xyz next = {now.xz + direction.xz,now.y + direction.y};
    if((next.y > 3) || (next.y < 0) || (next.xz >15) || (next.xz <0) ){
      return false; // would take us off the board
    }
    if(next.xz %4 == 0 && direction.xz == 1){
     return false;
    } 
    if(now.xz %4 == 0 && direction.xz == -1){
      return false;
    }
    
    return true;
    
}

bool inverse(xyz a,xyz b){
  if((a.xz + b.xz == 0) && (a.y + b.y == 0)){
    return true;
  }
  else{
    return false;
  }
}
