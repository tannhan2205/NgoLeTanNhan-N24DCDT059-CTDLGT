#include "DuongDiNhoNhat.hpp"
#include <random>
#include <chrono>
#include <iostream>
using namespace DT053;
int main(){
  int sizes[3]={3,5,10};
  for(int q=0;q<3;q++){
    int n=sizes[q]; std::mt19937 rng(2026+q); std::uniform_int_distribution<int> U(0,99);
    MaTran C(n,std::vector<int>(n)); for(auto&r:C)for(auto&v:r)v=U(rng);
    auto kq=duong_di_nho_nhat(C);
    long long dp1=tinh_tong_nho_nhat_toi_uu_bo_nho(C);
    auto g=giai_tham_lam(C,kq.tong_chi_phi); auto dj=giai_dijkstra(C);
    auto all=tim_tat_ca_duong_toi_uu(C,kq.f);
    const int R=200000; volatile long long sink=0;
    auto t0=std::chrono::steady_clock::now();
    for(int r=0;r<R;r++){ auto f=tinh_bang_quy_hoach_dong(C); sink+=f[n-1][n-1]; }
    auto t1=std::chrono::steady_clock::now();
    double us=std::chrono::duration<double,std::micro>(t1-t0).count()/R;
    std::cout<<"Q"<<q+1<<" "<<n<<"x"<<n<<" cells="<<n*n<<" cmp="<<(n-1)*(n-1)<<" trace="<<2*n-2
      <<" tong="<<kq.tong_chi_phi<<" buoc="<<kq.duong_di.size()<<" dp1d="<<dp1<<" greedy="<<g.tong_chi_phi
      <<" dijkstra="<<dj.tong_chi_phi<<" soduong="<<all.size()<<" bytes2D="<<n*n*8<<" bytes1D="<<n*8
      <<" us="<<us<<" valid="<<kiem_tra_duong(C,kq.duong_di,kq.tong_chi_phi)<<"\n";
    std::cout<<"  C="; for(auto&r:C){std::cout<<"[";for(int j=0;j<n;j++)std::cout<<r[j]<<(j+1<n?" ":"");std::cout<<"]";} std::cout<<"\n";
  }
}
