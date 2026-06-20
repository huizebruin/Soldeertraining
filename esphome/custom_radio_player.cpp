#include "esphome/custom_radio_player.h"
#include "esphome.h"
#include "esp_log.h"

static const char *TAG = "custom_radio";

namespace esphome {
namespace custom_radio {

RadioPlayer::RadioPlayer()
: current_index_(0), speaker_(nullptr), i2s_audio_(nullptr), playing_(false), paused_(false), volume_(1.0f), muted_(false), stop_stream_(false) {
}

RadioPlayer::~RadioPlayer() {
  stop();
}

void RadioPlayer::setup() {
  ESP_LOGI(TAG, "RadioPlayer setup");
  // add a default station so we have something to test with
  if (stations_.empty()) {
    stations_.push_back({"Example", "http://stream.example/stream.mp3"});
    current_station_name_ = stations_[0].name;
    current_station_url_ = stations_[0].url;
  }
}

void RadioPlayer::dump_config() {
  ESP_LOGI(TAG, "RadioPlayer: current_index=%d playing=%d stations=%d", current_index_, playing_, (int)stations_.size());
}

void RadioPlayer::loop() {
  // placeholder: monitor streaming thread or status
}

void RadioPlayer::play_media(const std::string &url) {
  ESP_LOGI(TAG, "play_media: %s", url.c_str());
  stop();
  current_station_url_ = url;
  // In a full implementation, start streaming thread here
  playing_ = true;
}

void RadioPlayer::pause() {
  ESP_LOGI(TAG, "pause");
  paused_ = true;
}

void RadioPlayer::resume() {
  ESP_LOGI(TAG, "resume");
  paused_ = false;
}

void RadioPlayer::stop() {
  ESP_LOGI(TAG, "stop");
  stop_stream_ = true;
  playing_ = false;
}

void RadioPlayer::set_volume(float volume) {
  volume_ = volume;
  ESP_LOGI(TAG, "set_volume: %f", volume);
}

void RadioPlayer::mute(bool mute) {
  muted_ = mute;
  ESP_LOGI(TAG, "mute: %d", mute);
}

void RadioPlayer::next() {
  if (stations_.empty()) return;
  current_index_ = (current_index_ + 1) % stations_.size();
  current_station_name_ = stations_[current_index_].name;
  current_station_url_ = stations_[current_index_].url;
  ESP_LOGI(TAG, "next -> idx=%d url=%s", current_index_, current_station_url_.c_str());
  play_media(current_station_url_);
}

void RadioPlayer::previous() {
  if (stations_.empty()) return;
  if (current_index_ == 0) current_index_ = stations_.size() - 1;
  else --current_index_;
  current_station_name_ = stations_[current_index_].name;
  current_station_url_ = stations_[current_index_].url;
  ESP_LOGI(TAG, "previous -> idx=%d url=%s", current_index_, current_station_url_.c_str());
  play_media(current_station_url_);
}

void RadioPlayer::add_station(const std::string &name, const std::string &url) {
  stations_.push_back({name, url});
}

void RadioPlayer::set_station(uint8_t idx) {
  if (idx >= stations_.size()) return;
  current_index_ = idx;
  current_station_name_ = stations_[idx].name;
  current_station_url_ = stations_[idx].url;
  play_media(current_station_url_);
}

void RadioPlayer::stream_thread_() {
  // Placeholder for streaming implementation
}

void RadioPlayer::fetch_and_play_(const std::string &url) {
  // Placeholder for HTTP fetch + decode + I2S write
}

}  // namespace custom_radio
}  // namespace esphome
